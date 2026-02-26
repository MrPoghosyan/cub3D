/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalieyan <natalieyan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by natalieyan        #+#    #+#             */
/*   Updated: 2026/02/19 03:04:06 by natalieyan       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_parser_and_game(const char *path, t_parser *p, t_game *game)
{
	p->line = NULL;
	p->map_lines = NULL;
	p->map_count = 0;
	p->in_map = 0;
	if (!path || !game)
	{
		print_err("parse_game: invalid arguments");
		return (0);
	}
	p->fd = open(path, O_RDONLY);
	if (p->fd < 0)
	{
		printf("Error\nparse_game: failed to open file %s\n", path);
		return (0);
	}
	game->textures.no_path = NULL;
	game->textures.so_path = NULL;
	game->textures.we_path = NULL;
	game->textures.ea_path = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	return (1);
}

char	*str_trim_left(char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

static int	set_texture_tag(char *t, t_game *game)
{
	char	*v;
	char	**dest;

	dest = NULL;
	if (t[0] == 'N' && t[1] == 'O' && t[2] == ' ')
		dest = &game->textures.no_path;
	else if (t[0] == 'S' && t[1] == 'O' && t[2] == ' ')
		dest = &game->textures.so_path;
	else if (t[0] == 'W' && t[1] == 'E' && t[2] == ' ')
		dest = &game->textures.we_path;
	else if (t[0] == 'E' && t[1] == 'A' && t[2] == ' ')
		dest = &game->textures.ea_path;
	else
		return (0);
	v = ft_strtrim(t + 3, " \t\n");
	if (!v)
		err("Memory allocation failed for texture path");
	*dest = v;
	return (1);
}

static int	set_color_tag(char *t, t_game *game)
{
	char	*v;
	t_color	*dest;

	if (t[0] == 'F' && t[1] == ' ')
		dest = &game->floor_color;
	else if (t[0] == 'C' && t[1] == ' ')
		dest = &game->ceiling_color;
	else
		return (0);
	v = ft_strtrim(t + 2, " \t\n");
	if (!v)
		err("Memory allocation failed for color");
	if (!validate_color(v, dest))
	{
		free(v);
		print_err("Invalid color configuration");
		exit(EXIT_FAILURE);
	}
	free(v);
	return (1);
}

int	parse_header_line(char *t, t_game *game)
{
	if (set_texture_tag(t, game))
		return (1);
	if (set_color_tag(t, game))
		return (1);
	return (0);
}
