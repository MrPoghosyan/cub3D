#include "cub3D.h"

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

int	validate_textures(t_texture *textures)
{
	int	fd;

	if (!textures)
	{
		print_err("Missing textures structure");
		return (0);
	}
	if (!textures->no_path || !textures->so_path ||
			!textures->we_path || !textures->ea_path)
	{
		print_err("One or more texture paths are missing");
		return (0);
	}
	fd = open(textures->no_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture NO: %s\n",
				textures->no_path);
		return (0);
	}
	close(fd);
	fd = open(textures->so_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture SO: %s\n",
				textures->so_path);
		return (0);
	}
	close(fd);
	fd = open(textures->we_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture WE: %s\n",
				textures->we_path);
		return (0);
	}
	close(fd);
	fd = open(textures->ea_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture EA: %s\n",
				textures->ea_path);
		return (0);
	}
	close(fd);
	return (1);
}

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
