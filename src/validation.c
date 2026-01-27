#include "cub3D.h"

// Պարսինգա անում և RGB գույնի տողը, պահում է `t_color structure ում
int	validate_color(char *color_str, t_color *color)
{
	int	r;
	int	g;
	int	b;

	if (!color_str || !color)
		return (0);
	if (!parse_rgb(color_str, &r, &g, &b))
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

// Ստուգումա որ բոլոր texture ֆայլերը գոյություն ունեն և կարդացվում են
int	validate_textures(t_texture *textures)
{
	int	fd;

	if (!textures)
	{
		print_err("Missing textures structure");
		return (0);
	}
	if (!textures->no || !textures->so || !textures->we || !textures->ea)
	{
		print_err("One or more texture paths are missing");
		return (0);
	}
	fd = open(textures->no, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture NO: %s\n", textures->no);
		return (0);
	}
	close(fd);
	fd = open(textures->so, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture SO: %s\n", textures->so);
		return (0);
	}
	close(fd);
	fd = open(textures->we, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture WE: %s\n", textures->we);
		return (0);
	}
	close(fd);
	fd = open(textures->ea, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture EA: %s\n", textures->ea);
		return (0);
	}
	close(fd);
	return (1);
}

// Վավերացնումա ամբողջ քարտեզը ստուգումա յուրաքանչյուր բջիջը, ունի միայն մեկ խաղացող և ճիշտ շրջափակում առաջին if ը
int	validate_map(t_map *map)
{
	int	y;
	int	x;
	int	player_count;
	int	res;

	player_count = 0;
	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		return (0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			res = process_cell(map, y, x, &player_count);
			if (res == 0)
				return (0);
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		printf("Error\nPlayer count invalid: %d (expected 1)\n",
			player_count);
		return (0);
	}
	return (1);
}
