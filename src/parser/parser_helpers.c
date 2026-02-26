/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalieyan <natalieyan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by natalieyan        #+#    #+#             */
/*   Updated: 2026/02/19 03:06:50 by natalieyan       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	append_map_line(t_parser *p, char *s)
{
	char	*copy;
	char	**new;
	int		i;

	copy = ft_strdup(s);
	if (!copy)
		err("Memory allocation failed while copying map line");
	new = malloc(sizeof(char *) * (p->map_count + 2));
	if (!new)
	{
		free(copy);
		err("Memory allocation failed while expanding map storage");
	}
	i = 0;
	while (i < p->map_count)
	{
		new[i] = p->map_lines[i];
		i++;
	}
	new[p->map_count] = copy;
	new[p->map_count + 1] = NULL;
	free(p->map_lines);
	p->map_lines = new;
	p->map_count++;
	return (1);
}

void	compute_map_width(t_parser *p, t_game *game)
{
	int	maxw;
	int	i;
	int	l;

	maxw = 0;
	i = 0;
	while (i < p->map_count)
	{
		l = ft_strlen(p->map_lines[i]);
		if (l > maxw)
			maxw = l;
		i++;
	}
	game->map.width = maxw;
}

static void	trim_line(t_parser *p)
{
	int	tl;

	p->s = p->line;
	if (p->s && p->s[0])
	{
		tl = ft_strlen(p->s) - 1;
		if (tl >= 0 && (p->s[tl] == '\n' || p->s[tl] == '\r'))
			p->s[tl] = '\0';
	}
	p->t = str_trim_left(p->s);
	if (!p->in_map && (*p->t == '1' || *p->t == '0' || *p->t == ' '))
		p->in_map = 1;
}

static int	process_current_line(t_parser *p, t_game *game)
{
	if (!p || !p->line)
		return (0);
	trim_line(p);
	if (!p->in_map)
	{
		p->parsed = parse_header_line(p->t, game);
		if (p->parsed == -1)
			err("Invalid header configuration");
	}
	else
	{
		if (!append_map_line(p, p->s))
			err("Failed to append map line");
	}
	return (1);
}

int	read_lines(t_parser *p, t_game *game)
{
	char	*next;

	while (p->line)
	{
		if (!process_current_line(p, game))
			return (0);
		free(p->line);
		next = get_next_line(p->fd);
		p->line = next;
		p->rd = (p->line != NULL);
	}
	return (1);
}
