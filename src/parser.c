#include "cub3D.h"

static char	*str_trim_left(char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

static char	*dup_trimmed(char *s)
{
	char	*t;

	t = ft_strtrim(s, " \t\n");
	return (t);
}

static int	starts_with(const char *s, const char *p)
{
	while (*p)
	{
		if (*s == '\0' || *s != *p)
			return (0);
		s++;
		p++;
	}
	return (1);
}

static void	free_str_list(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	parse_game(const char *path, t_game *game)
{
	FILE	*f;
	char	*line;
	size_t	len;
	ssize_t	read;
	char	**map_lines;
	int		map_count;
	int		in_map;
	char	*s;
	char	*t;
	char	*v;
	char	*v;
	char	*v;
	char	*v;
	char	*v;
	char	*v;
	char	*copy;
	char	**new;
	int		maxw;
	int		l;

	line = NULL;
	len = 0;
	map_lines = NULL;
	map_count = 0;
	if (!path || !game)
		return (0);
	f = fopen(path, "r");
	if (!f)
		return (0);
	/* init */
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	in_map = 0;
	while ((read = getline(&line, &len, f)) != -1)
	{
		s = line;
		if (read > 0 && s[read - 1] == '\n')
			s[read - 1] = '\0';
		t = str_trim_left(s);
		if (!in_map && (*t == '1' || *t == '0' || *t == ' '))
			in_map = 1;
		if (!in_map)
		{
			if (starts_with(t, "NO "))
			{
				v = dup_trimmed(t + 3);
				if (!v)
				{
					fclose(f);
					free(line);
					return (0);
				}
				game->textures.no = v;
			}
			else if (starts_with(t, "SO "))
			{
				v = dup_trimmed(t + 3);
				if (!v)
				{
					fclose(f);
					free(line);
					return (0);
				}
				game->textures.so = v;
			}
			else if (starts_with(t, "WE "))
			{
				v = dup_trimmed(t + 3);
				if (!v)
				{
					fclose(f);
					free(line);
					return (0);
				}
				game->textures.we = v;
			}
			else if (starts_with(t, "EA "))
			{
				v = dup_trimmed(t + 3);
				if (!v)
				{
					fclose(f);
					free(line);
					return (0);
				}
				game->textures.ea = v;
			}
			else if (starts_with(t, "F "))
			{
				v = dup_trimmed(t + 2);
				if (!v)
				{
					fclose(f);
					free(line);
					return (0);
				}
				if (!validate_color(v, &game->floor_color))
				{
					free(v);
					fclose(f);
					free(line);
					return (0);
				}
				free(v);
			}
			else if (starts_with(t, "C "))
			{
				v = dup_trimmed(t + 2);
				if (!v)
				{
					fclose(f);
					free(line);
					return (0);
				}
				if (!validate_color(v, &game->ceiling_color))
				{
					free(v);
					fclose(f);
					free(line);
					return (0);
				}
				free(v);
			}
			else if (*t == '\0')
			{
			}
			else
			{
			}
		}
		else
		{
			copy = ft_strdup(s);
			if (!copy)
			{
				fclose(f);
				free(line);
				free_str_list(map_lines);
				return (0);
			}
			new = malloc(sizeof(char *) * (map_count + 2));
			if (!new)
			{
				free(copy);
				fclose(f);
				free(line);
				free_str_list(map_lines);
				return (0);
			}
			for (int i = 0; i < map_count; ++i)
				new[i] = map_lines[i];
			new[map_count] = copy;
			new[map_count + 1] = NULL;
			free(map_lines);
			map_lines = new;
			map_count++;
		}
	}
	free(line);
	fclose(f);
	if (map_count == 0)
	{
		free_str_list(map_lines);
		return (0);
	}
	game->map.grid = map_lines;
	game->map.height = map_count;
	maxw = 0;
	for (int i = 0; i < map_count; ++i)
	{
		l = ft_strlen(map_lines[i]);
		if (l > maxw)
			maxw = l;
	}
	game->map.width = maxw;
	if (!validate_textures(&game->textures))
		return (0);
	if (!validate_map(&game->map))
		return (0);
	return (1);
}
