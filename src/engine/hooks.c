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

int	key_press(int keycode, t_cub *cub)
{
	(void)cub;

	if (keycode == 65307) // ESC
		return close_game(cub);
	return (0);
}
