#include "cub3D.h"

static int	get_char_at(t_map *map, int y, int x)
{
	if (!map || !map->grid)
		return (' ');
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

int	parse_rgb(char *color_str, int *r, int *g, int *b)
{
	char	extra;

	if (!color_str || !r || !g || !b)
	{
		print_err("Invalid color string or NULL target");
		return (0);
	}
	if (sscanf(color_str, " %d , %d , %d %c", r, g, b, &extra) != 3)
	{
		print_err("Color must be three integers separated by commas");
		return (0);
	}
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		printf("Error\n (got %d,%d,%d)\n", *r, *g, *b);
		return (0);
	}
	return (1);
}

int	cell_enclosed(t_map *map, int y, int x)
{
	if (!map || !map->grid)
		return (0);
	if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)
		return (0);
	if (get_char_at(map, y - 1, x) == ' ' || get_char_at(map, y + 1, x) == ' '
		|| get_char_at(map, y, x - 1) == ' ' || get_char_at(map, y, x
			+ 1) == ' ')
		return (0);
	return (1);
}

int	process_cell(t_map *map, int y, int x, int *player_count)
{
	char	c;

	c = get_char_at(map, y, x);
	if (c == '\0')
		c = ' ';
	if (!(c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
			|| c == 'W'))
	{
		printf("Error\nInvalid map character '%c' at (%d,%d)\n", c, y, x);
		return (0);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player_count)++;
		map->player_x = x;
		map->player_y = y;
		map->player_dir = c;
	}
	if ((c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		&& !cell_enclosed(map, y, x))
	{
		printf("Error\nMap cell at (%d,%d) is not enclosed\n", y, x);
		return (0);
	}
	return (1);
}
