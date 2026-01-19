#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!parse_game(argv[1], &game))
	{
		printf("Validation failed\n");
		return (1);
	}
	printf("Validation OK\n");
	return (0);
}
