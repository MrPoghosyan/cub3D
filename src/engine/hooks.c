#include "cub3D.h"

int	close_game(t_cub *cub)
{
	free_cub(cub);
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
		move_left(cub);
	if (keycode == 'd')
		move_right(cub);
	if (keycode == 65361) // <--
		turn_left(cub);
	if (keycode == 65363) // -->
		turn_right(cub);
		
	return (0);
}
