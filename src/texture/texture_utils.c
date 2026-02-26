#include "cub3D.h"

int	get_tex_pixel(t_tex_img *tex, int x, int y)
{
	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	return (tex->addr[y * (tex->line_len / 4) + x]);
}

t_tex_img	*select_texture(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&cub->game.textures.we);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (&cub->game.textures.ea);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		return (&cub->game.textures.no);
	return (&cub->game.textures.so);
}
