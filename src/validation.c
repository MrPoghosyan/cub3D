#include "cub3D.h"

static void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	validate_color(char *color_str, t_color *color)
{
	char	**values;
	char	*trimmed0;
	char	*trimmed1;
	char	*trimmed2;
	int		r;
	int		g;
	int		b;

	if (!color_str || !color)
		return (0);
	values = ft_split(color_str, ',');
	if (!values)
		return (0);
	if (!values[0] || !values[1] || !values[2] || values[3])
	{
		free_str_array(values);
		return (0);
	}
	trimmed0 = ft_strtrim(values[0], " \t\n");
	trimmed1 = ft_strtrim(values[1], " \t\n");
	trimmed2 = ft_strtrim(values[2], " \t\n");
	free_str_array(values);
	if (!trimmed0 || !trimmed1 || !trimmed2)
	{
		free(trimmed0);
		free(trimmed1);
		free(trimmed2);
		return (0);
	}
	r = ft_atoi(trimmed0);
	g = ft_atoi(trimmed1);
	b = ft_atoi(trimmed2);
	free(trimmed0);
	free(trimmed1);
	free(trimmed2);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
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
		return (0);
	if (!textures->no || !textures->so || !textures->we || !textures->ea)
		return (0);
	fd = open(textures->no, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(textures->so, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(textures->we, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(textures->ea, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	get_char_at(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (' ');
	if (!map->grid[y])
		return (' ');
	if (x < 0)
		return (' ');
	if (x >= (int)ft_strlen(map->grid[y]))
		return (' ');
	return ((int)map->grid[y][x]);
}

int	validate_map(t_map *map)
{
	int		y;
	int		x;
	int		player_count;
	char	c;

	player_count = 0;
	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		return (0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = get_char_at(map, y, x);
			if (c == '\0')
				c = ' ';
			if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
				return (0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_count++;
				map->player_x = x;
				map->player_y = y;
				map->player_dir = c;
			}
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (y == 0 || x == 0 || y == map->height - 1 || x == map->width
					- 1)
					return (0);
				if (get_char_at(map, y - 1, x) == ' ' || get_char_at(map, y + 1,
						x) == ' ' || get_char_at(map, y, x - 1) == ' '
					|| get_char_at(map, y, x + 1) == ' ')
					return (0);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}
