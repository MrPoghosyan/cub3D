#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		err("Invalid count of arguments\n");
	cub = init_game(av[1]);
	init_player(cub);
	engine_init(cub);
	mlx_loop(cub->mlx);
	free_cub(cub);
}
