#include "cub3D.h"

void	ray_step_calc(t_cub *cub, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (cub->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - cub->player.x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (cub->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - cub->player.y) * ray->delta_y;
	}
}

void	ray_dda(t_cub *cub, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (safe_cell(cub, ray->map_y, ray->map_x) == '1')
			ray->hit = 1;
	}
}

void	ray_distance(t_cub *cub, t_ray *ray, int h)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - cub->player.x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->perp_dist = (ray->map_y - cub->player.y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_h = (int)(h / ray->perp_dist);
	ray->draw_start = -ray->line_h / 2 + h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + h / 2;
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
}

void	render_3d(t_cub *cub)
{
	t_ray	ray;
	int		w;
	int		h;
	int		x;

	w = 1200;
	h = 800;
	x = 0;
	clear_image(cub, w, h);
	while (x < w)
	{
		ray_init(cub, &ray, x, w);
		ray_step_calc(cub, &ray);
		ray_dda(cub, &ray);
		ray_distance(cub, &ray, h);
		ray_draw(cub, &ray, x, h);
		x++;
	}
}
