#include "cub3D.h"

// Ձախ կողմի բացատները կտրում է տողից
static char	*str_trim_left(char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

// Պարսում է header տողերը (NO, SO, WE, EA, F, C) և պահում խաղի կառուցվածքում
int	parse_header_line(char *t, t_game *game)
{
	char	*v;

	if (t[0] == 'N' && t[1] == 'O' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			fprintf(stderr, "Error\nMemory allocation failed for texture NO\n");
			exit(EXIT_FAILURE);
		}
		game->textures.no = v;
		return (1);
	}
	if (t[0] == 'S' && t[1] == 'O' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			fprintf(stderr, "Error\nMemory allocation failed for texture SO\n");
			exit(EXIT_FAILURE);
		}
		game->textures.so = v;
		return (1);
	}
	if (t[0] == 'W' && t[1] == 'E' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			fprintf(stderr, "Error\nMemory allocation failed for texture WE\n");
			exit(EXIT_FAILURE);
		}
		game->textures.we = v;
		return (1);
	}
	if (t[0] == 'E' && t[1] == 'A' && t[2] == ' ')
	{
		v = ft_strtrim(t + 3, " \t\n");
		if (!v)
		{
			fprintf(stderr, "Error\nMemory allocation failed for texture EA\n");
			exit(EXIT_FAILURE);
		}
		game->textures.ea = v;
		return (1);
	}
	if (t[0] == 'F' && t[1] == ' ')
	{
		v = ft_strtrim(t + 2, " \t\n");
		if (!v)
		{
			fprintf(stderr,
				"Error\nMemory allocation failed for floor color\n");
			exit(EXIT_FAILURE);
		}
		if (!validate_color(v, &game->floor_color))
		{
			free(v);
			fprintf(stderr, "Error\nInvalid floor color configuration\n");
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
			fprintf(stderr,
				"Error\nMemory allocation failed for ceiling color\n");
			exit(EXIT_FAILURE);
		}
		if (!validate_color(v, &game->ceiling_color))
		{
			free(v);
			fprintf(stderr, "Error\nInvalid ceiling color configuration\n");
			exit(EXIT_FAILURE);
		}
		free(v);
		return (1);
	}
	return (0);
}

// Ավելացնում է քարտեզի տող պարսերի map_lines զանգվածին,ընդլայնելով անհրաժեշտության դեպքում

int	append_map_line(t_parser *p, char *s)
{
	char	*copy;
	char	**new;
	int		i;

	copy = ft_strdup(s);
	if (!copy)
	{
		fprintf(stderr,
			"Error\nMemory allocation failed while copying map line\n");
		exit(EXIT_FAILURE);
	}
	new = malloc(sizeof(char *) * (p->map_count + 2));
	if (!new)
	{
		free(copy);
		fprintf(stderr,
			"Error\nMemory allocation failed while expanding map storage\n");
		exit(EXIT_FAILURE);
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

// Հիմնական օղակ՝ կարդում և մշակում է յուրաքանչյուր տողը ֆայլից
int	read_lines(t_parser *p, t_game *game)
{
	while (p->rd != -1)
	{
		p->s = p->line;
		if (p->rd > 0 && p->s[p->rd - 1] == '\n')
			p->s[p->rd - 1] = '\0';
		p->t = str_trim_left(p->s);
		if (!p->in_map && (*p->t == '1' || *p->t == '0' || *p->t == ' '))
			p->in_map = 1;
		if (!p->in_map)
		{
			p->parsed = parse_header_line(p->t, game);
			if (p->parsed == -1)
			{
				fprintf(stderr, "Error\nInvalid header configuration\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (!append_map_line(p, p->s))
			{
				fprintf(stderr, "Error\nFailed to append map line\n");
				exit(EXIT_FAILURE);
			}
		}
		p->rd = getline(&p->line, &p->len, p->f);
	}
	return (1);
}
