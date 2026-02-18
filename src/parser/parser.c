/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalieyan <natalieyan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by natalieyan        #+#    #+#             */
/*   Updated: 2026/02/19 02:56:34 by natalieyan       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	read_file_lines(t_parser *p, t_game *game)
{
	p->line = get_next_line(p->fd);
	p->rd = (p->line != NULL);
	if (!read_lines(p, game))
	{
		close(p->fd);
		free(p->line);
		free_str_array(p->map_lines);
		print_err("parse_game: read_lines failed");
		return (0);
	}
	free(p->line);
	close(p->fd);
	return (1);
}

int	setup_map(t_parser *p, t_game *game)
{
	if (p->map_count == 0)
	{
		free_str_array(p->map_lines);
		print_err("parse_game: no map data found");
		return (0);
	}
	game->map.grid = p->map_lines;
	game->map.height = p->map_count;
	compute_map_width(p, game);
	return (1);
}

int	validate_game_data(t_game *game)
{
	if (!validate_textures(&game->textures))
	{
		print_err("parse_game: texture validation failed");
		return (0);
	}
	if (!validate_map(&game->map))
	{
		print_err("parse_game: map validation failed");
		return (0);
	}
	return (1);
}

int	read_and_validate(t_parser *p, t_game *game)
{
	if (!read_file_lines(p, game))
		return (0);
	if (!setup_map(p, game))
		return (0);
	if (!validate_game_data(game))
		return (0);
	return (1);
}

int	parse_game(const char *path, t_game *game)
{
	t_parser	p;

	if (!init_parser_and_game(path, &p, game))
		return (0);
	if (!read_and_validate(&p, game))
		return (0);
	return (1);
}
