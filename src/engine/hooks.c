#include "engine.h"

int	close_game(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
#ifdef __linux__
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
#endif
	free(cub);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 65307) // ESC
		return close_game(cub);
	if (keycode == 'w')
		move_forward(cub);
	if (keycode == 's')
		move_backward(cub);
	if (keycode == 'a')
		turn_left(cub);
	if (keycode == 'd')
		turn_right(cub);
#if DEBUG_2D // dellet
	draw_map_2d(cub);
#endif
	return (0);
}
