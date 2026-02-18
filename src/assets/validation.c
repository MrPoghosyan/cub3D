/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalieyan <natalieyan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by natalieyan        #+#    #+#             */
/*   Updated: 2026/02/18 17:28:02 by natalieyan       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_texture_path(char *path, char *id)
{
	int	fd;

	if (!path)
	{
		printf("Error\nTexture %s path missing\n", id);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open texture %s: %s\n", id, path);
		return (0);
	}
	close(fd);
	return (1);
}

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
	if (!textures)
	{
		print_err("Missing textures structure");
		return (0);
	}
	if (!textures->no_path || !textures->so_path || !textures->we_path
		|| !textures->ea_path)
	{
		print_err("One or more texture paths are missing");
		return (0);
	}
	if (!check_texture_path(textures->no_path, "NO"))
		return (0);
	if (!check_texture_path(textures->so_path, "SO"))
		return (0);
	if (!check_texture_path(textures->we_path, "WE"))
		return (0);
	if (!check_texture_path(textures->ea_path, "EA"))
		return (0);
	return (1);
}

static int	validate_map_cells(t_map *map, int *player_count)
{
	int	y;
	int	x;
	int	res;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			res = process_cell(map, y, x, player_count);
			if (res == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	int	player_count;

	player_count = 0;
	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		return (0);
	if (!validate_map_cells(map, &player_count))
		return (0);
	if (player_count != 1)
	{
		printf("Error\nPlayer count invalid: %d (expected 1)\n", player_count);
		return (0);
	}
	return (1);
}
