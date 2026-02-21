#include "cub3D.h"

void	render_frame(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);
	render_3d(cub);
}

int	engine_loop(t_cub *cub)
{
	render_3d(cub);
	minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}
