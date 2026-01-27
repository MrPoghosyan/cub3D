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

void	init_player(t_cub *cub)
{
	cub->player.x = cub->game.map.player_x + 0.5;
	cub->player.y = cub->game.map.player_y + 0.5;
	cub->player.dir_x = -1.0;
	cub->player.dir_y = 0.0;
	cub->piayer.plane_x = 0.0;
	cub->piayer.plane_y = 0.66;
}

int		engine_loop(t_cub *cub)
{
	render_frame(cub);
	return (0);
}
