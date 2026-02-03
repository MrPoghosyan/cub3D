#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		err("Invalid count of arguments\n");
	cub = init_game(av[1]);
	init_player(cub);
	engine_init(cub);
	printf("PLAYER MAP POS: %d %d\n",
			cub->game.map.player_x,
			cub->game.map.player_y);

	printf("PLAYER REAL POS: %f %f\n",
			cub->player.x,
			cub->player.y);

	mlx_loop(cub->mlx);
	free_cub(cub);
}
