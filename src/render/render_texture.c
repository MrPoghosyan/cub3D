#include "cub3D.h"

static double  calc_wall_x(t_cub *cub, t_ray *ray)
{
    double  wall_x;

    if (ray->side == 0)
        wall_x = cub->player.y + ray->perp_dist * ray->ray_dir_y;
    else
        wall_x = cub->player.x + ray->perp_dist * ray->ray_dir_x;
    return (wall_x - my_floor(wall_x));
}

static int calc_tex_x(t_cub *cub, t_ray *ray, t_tex_img *tex)
{
    double  wall_x;
    int     tex_x;

    wall_x = calc_wall_x(cub, ray);
    tex_x = (int)(wall_x * tex->width);
    if (ray->side == 0 && ray->ray_dir_x > 0)
        tex_x = tex->width - tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        tex_x = tex->width - tex_x - 1;
    return (tex_x);
}

static void init_tex_step(t_ray *ray, t_tex_img *tex,
                   double *step, double *tex_pos, int h)
{
    *step = 1.0 * tex->height / ray->line_h;
    *tex_pos = (ray->draw_start - h / 2
        + ray->line_h / 2) * (*step);
}

static void draw_wall_column(t_cub *cub, t_ray *ray,
                      t_tex_img *tex, int x)
{
    double  tex_pos;
    double  step;
    double  shade;
    int     tex_y;
    int     y;
    int     color;

    init_tex_step(ray, tex, &step, &tex_pos, 800);
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        color = get_tex_pixel(tex, ray->tex_x, tex_y);
        shade = 1.0 / (1.0 + ray->perp_dist * 0.15);
        color = apply_shade(color, shade);
        img_pixel_put(&cub->img, x, y, color);
        y++;
    }
}

static int interpolate(int c1, int c2, double t)
{
    int r;
    int g;
    int b;

    r = ((c1 >> 16) & 0xFF) * (1 - t)
        + ((c2 >> 16) & 0xFF) * t;
    g = ((c1 >> 8) & 0xFF) * (1 - t)
        + ((c2 >> 8) & 0xFF) * t;
    b = (c1 & 0xFF) * (1 - t)
        + (c2 & 0xFF) * t;

    return ((r << 16) | (g << 8) | b);
}
/*
static void draw_floor_ceiling(t_cub *cub, int x, int h)
{
    int y;
    int top_color;
    int bottom_color;
    int floor_color;
    double t;
    int color;

    top_color = 0x87CEEB;      // sky blue top
    bottom_color = color_to_int(cub->game.ceiling_color);
    floor_color = color_to_int(cub->game.floor_color);

    y = 0;
    while (y < h)
    {
        if (y < h / 2)
        {
            t = (double)y / (h / 2);
            color = interpolate(top_color, bottom_color, t);
        }
        else
            color = floor_color;

        img_pixel_put(&cub->img, x, y, color);
        y++;
    }
}
*/
static void draw_floor_ceiling(t_cub *cub, int x)
{
    int y;
    int screen_h;
    int top_color;
    int horizon_color;
    int floor_color;
    double t;
    int color;

    screen_h = 800;

    top_color = 0x1B3B6F;      // darker blue
    horizon_color = 0x87CEEB;  // light sky
    floor_color = color_to_int(cub->game.floor_color);

    y = 0;
    while (y < screen_h)
    {
        if (y < screen_h / 2)
        {
            t = (double)y / (screen_h / 2);
            color = interpolate(top_color, horizon_color, t);
        }
        else
            color = floor_color;

        img_pixel_put(&cub->img, x, y, color);
        y++;
    }
}

void ray_draw(t_cub *cub, t_ray *ray, int x, int h)
{
    t_tex_img  *tex;

    (void)h;
    draw_floor_ceiling(cub, x);
    tex = select_texture(cub, ray);
    ray->tex_x = calc_tex_x(cub, ray, tex);
    draw_wall_column(cub, ray, tex, x);
}
