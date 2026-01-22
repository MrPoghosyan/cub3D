#include "cub3D.h"
#include "engine.h"

t_cub	*init_game(char *path)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		err("malloc failed");
	ft_memset(cub, 0, sizeof(t_cub));
	if (!parse_game(path, &cub->game))
	{
		free(cub);
		err("parse failed");
	}
	return (cub);
}

void	free_cub(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	free(cub);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		err("Invalid count of arguments\n");
	cub = init_game(av[1]);
	engine_init(cub);
	mlx_loop(cub->mlx);
	free_cub(cub);
}
