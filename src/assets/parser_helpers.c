#include "cub3D.h"

static char	*str_trim_left(char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

int	parse_header_line(char *t, t_game *game)
{
	char	*v;

	if (t[0] == 'N' && t[1] == 'O' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			err("Memory allocation failed for texture NO");
		}
		game->textures.no = v;
		return (1);
	}
	if (t[0] == 'S' && t[1] == 'O' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			err("Memory allocation failed for texture SO");
		}
		game->textures.so = v;
		return (1);
	}
	if (t[0] == 'W' && t[1] == 'E' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			err("Memory allocation failed for texture WE");
		}
		game->textures.we = v;
		return (1);
	}
	if (t[0] == 'E' && t[1] == 'A' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			err("Memory allocation failed for texture EA");
		}
		game->textures.ea = v;
		return (1);
	}
	if (t[0] == 'F' && t[1] == ' ')
	{
		v = ft_strtrim(t + 2, " \t\n");
		if (!v)
		{
			err("Memory allocation failed for floor color");
		}
		if (!validate_color(v, &game->floor_color))
		{
			free(v);
			print_err("Invalid floor color configuration");
			exit(EXIT_FAILURE);
		}
		free(v);
		return (1);
	}
	if (t[0] == 'C' && t[1] == ' ')
	{
		v = ft_strtrim(t + 2, " \t\n");
		if (!v)
		{
			err("Memory allocation failed for ceiling color");
		}
		if (!validate_color(v, &game->ceiling_color))
		{
			free(v);
			print_err("Invalid ceiling color configuration");
			exit(EXIT_FAILURE);
		}
		free(v);
		return (1);
	}
	return (0);
}

int	append_map_line(t_parser *p, char *s)
{
	char	*copy;
	char	**new;
	int		i;

	copy = ft_strdup(s);
	if (!copy)
	{
		err("Memory allocation failed while copying map line");
	}
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

int	read_lines(t_parser *p, t_game *game)
{
	char	*next;
	int		tl;

	while (p->line)
	{
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
		if (!p->in_map)
		{
			p->parsed = parse_header_line(p->t, game);
			if (p->parsed == -1)
			{
				err("Invalid header configuration");
			}
		}
		else
		{
			if (!append_map_line(p, p->s))
			{
				err("Failed to append map line");
			}
		}
		free(p->line);
		next = get_next_line(p->fd);
		p->line = next;
		p->rd = (p->line != NULL);
	}
	return (1);
}
