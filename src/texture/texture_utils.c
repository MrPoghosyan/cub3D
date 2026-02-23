#include "cub3D.h"

int	get_tex_pixel(t_tex_img *tex, int x, int y)
{
	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	return (tex->addr[y * (tex->line_len / 4) + x]);
}

t_tex_img	*select_texture(t_cub *cub, t_ray *ray)
{
	char	cell;

	cell = 'X';
	if (ray->map_y >= 0 && ray->map_y < cub->game.map.height)
	{
		if (ray->map_x >= 0
			&& ray->map_x < (int)ft_strlen(cub->game.map.grid[ray->map_y]))
			cell = cub->game.map.grid[ray->map_y][ray->map_x];
	}
	if (cell == 'C')
		return (&cub->game.textures.closed_door);
	if (cell == 'O')
		return (&cub->game.textures.open_door);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&cub->game.textures.we);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (&cub->game.textures.ea);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		return (&cub->game.textures.no);
	return (&cub->game.textures.so);
}
