#include "engine.h"

void	engine_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		err("mlx_init failed");
	cub->win = mlx_new_window(cub->mlx, 800, 600, "cub3D");
	if (!cub->win)
		err("mlx_new_window failed");
	mlx_hook(cub->win, 2, 1L << 0, key_hook, cub); // ESC key
	mlx_hook(cub->win, 17, 0, close_game, cub);     // close window button
	mlx_loop_hook(cub->mlx, engine_loop, cub);
}

int		engine_loop(t_cub *cub)
{
	render_frame(cub);
	return (0);
}
