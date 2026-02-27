#include "cub3D.h"

static double	calc_wall_x(t_cub *cub, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cub->player.y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = cub->player.x + ray->perp_dist * ray->ray_dir_x;
	return (wall_x - my_floor(wall_x));
}

static int	calc_tex_x(t_cub *cub, t_ray *ray, t_tex_img *tex)
{
	double	wall_x;
	int		tex_x;

	wall_x = calc_wall_x(cub, ray);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	init_tex_step(t_ray *ray, t_tex_img *tex,
double *step, double *tex_pos)
{
	int	h;

	h = 800;
	*step = 1.0 * tex->height / ray->line_h;
	*tex_pos = (ray->draw_start - h / 2
			+ ray->line_h / 2) * (*step);
}

static void	draw_wall_column(t_cub *cub, t_ray *ray,
t_tex_img *tex, int x)
{
	t_wall_draw	d;

	init_tex_step(ray, tex, &d.step, &d.tex_pos);
	d.y = ray->draw_start;
	while (d.y < ray->draw_end)
	{
		d.tex_y = (int)d.tex_pos & (tex->height - 1);
		d.tex_pos += d.step;
		d.color = get_tex_pixel(tex, ray->tex_x, d.tex_y);
		d.shade = 1.0 / (1.0 + ray->perp_dist * 0.15);
		d.color = apply_shade(d.color, d.shade);
		img_pixel_put(&cub->img, x, d.y, d.color);
		d.y++;
	}
}

void	ray_draw(t_cub *cub, t_ray *ray, int x, int h)
{
	t_tex_img	*tex;

	draw_floor_ceiling(cub, x, h);
	tex = select_texture(cub, ray);
	ray->tex_x = calc_tex_x(cub, ray, tex);
	draw_wall_column(cub, ray, tex, x);
}
