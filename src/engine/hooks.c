#include "cub3D.h"

int	close_game(t_cub *cub)
{
	mlx_loop_end(cub->mlx);
//	free_cub(cub);
//	exit(0);
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		return (close_game(cub));
	if (keycode == KEY_W)
		move_forward(cub);
	if (keycode == KEY_S)
		move_backward(cub);
	if (keycode == KEY_A)
		move_left(cub);
	if (keycode == KEY_D)
		move_right(cub);
	if (keycode == KEY_LEFT)
		turn_left(cub);
	if (keycode == KEY_RIGHT)
		turn_right(cub);
	if (keycode == KEY_O)
		try_to_open_door(cub);
	return (0);
}
