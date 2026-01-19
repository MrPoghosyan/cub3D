#include "cub3D.h"

void	err(char *msg)
{
	fprintf(stderr, "Error\n%s", msg);
	exit(1);
}

// Նախաստորագրում է խաղը՝ պարսելով .cub ֆայլը և ստեղծելով t_cub կառուցվածքը
t_cub	*init_game(char *path)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		err("malloc failed");
	memset(cub, 0, sizeof(t_cub));
	if (!parse_game(path, &cub->game))
	{
		free(cub);
		err("parse failed");
	}
	return (cub);
}

// Նախապատրաստում է MLX գրադարանը և ստեղծում խաղի պատուհան
void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		err("mlx_init failed");
	cub->win = mlx_new_window(cub->mlx, 800, 600, "cub3D");
	if (!cub->win)
		err("mlx_new_window failed");
	mlx_loop(cub->mlx);
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
	init_mlx(cub);
	free_cub(cub);
}
