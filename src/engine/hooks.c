#include "cub3D.h"

int	close_game(t_cub *cub)
{
	free_cub(cub);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 53) // ESC (macOS)
		return (close_game(cub));
	if (keycode == 13) // W (macOS)
		move_forward(cub);
	if (keycode == 1) // S (macOS)
		move_backward(cub);
	if (keycode == 0) // A (macOS)
		move_left(cub);
	if (keycode == 2) // D (macOS)
		move_right(cub);
	if (keycode == 123) // Left arrow (macOS)
		turn_left(cub);
	if (keycode == 124) // Right arrow (macOS)
		turn_right(cub);
	if (keycode == 49) // Spacebar
		try_to_open_door(cub);
	return (0);
}
