#include "cub3D.h"

// Վերադարձնում է նիշը քարտեզի դիրքում (y,x),վերադարձնում է բացատ եթե դուրս է սահմաններից 
static int get_char_at(t_map *map,
	int y, int x)
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

// Ազատում է տողերի զանգվածը և ինքը զանգվածը
void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Պարսում է RGB գույնի տողը "R,G,B" և վավերացնում է 0-255 տիրույթը (սաբջեքթով)
int	parse_rgb(char *color_str, int *r, int *g, int *b)
{
	char	**values;
	char	*t0;
	char	*t1;
	char	*t2;

	if (!color_str || !r || !g || !b)
	{
		fprintf(stderr, "Error\nInvalid color string or NULL target\n");
		return (0);
	}
	values = ft_split(color_str, ',');
	if (!values)
	{
		fprintf(stderr, "Error\nFailed to split color string\n");
		return (0);
	}
	if (!values[0] || !values[1] || !values[2] || values[3])
	{
		free_str_array(values);
		fprintf(stderr,
			"Error\nColor must have exactly 3 comma-separated values\n");
		return (0);
	}
	t0 = ft_strtrim(values[0], " \t\n");
	t1 = ft_strtrim(values[1], " \t\n");
	t2 = ft_strtrim(values[2], " \t\n");
	free_str_array(values);
	if (!t0 || !t1 || !t2)
	{
		free(t0);
		free(t1);
		free(t2);
		fprintf(stderr, "Error\nFailed to trim color components\n");
		return (0);
	}
	*r = ft_atoi(t0);
	*g = ft_atoi(t1);
	*b = ft_atoi(t2);
	free(t0);
	free(t1);
	free(t2);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
	{
		fprintf(stderr, "Error\n (got %d,%d,%d)\n", *r, *g, *b);
		return (0);
	}
	return (1);
}

// Ստուգում է արդյոք նիշը վավեր է քարտեզում (բացատ, պատ, հատակ,խաղացողի ուղղություններ)
int	is_map_char(char c)
	{
		if (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
			|| c == 'W')
			return (1);
		return (0);
	}

	// Ստուգում է արդյոք նիշը պետք է շրջապատվի պատերով (հատակներ և խաղացողներ)
	int needs_enclosure(char c)
	{
		if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			return (1);
		return (0);
	}

	// Ստուգում է,որ քարտեզի(y,x)արգումենտները պատշաճ փակված են պատերով բոլոր կողմերից
	int cell_enclosed(t_map *map, int y, int x)
	{
		if (!map || !map->grid)
			return (0);
		if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)
			return (0);
		if (get_char_at(map, y - 1, x) == ' ' || get_char_at(map, y + 1,
				x) == ' ' || get_char_at(map, y, x - 1) == ' '
			|| get_char_at(map, y, x + 1) == ' ')
			return (0);
		return (1);
	}

	// Մշակում է մեկ քարտեզի բջիջ. վավերացնում է նիշը,
	// հաշվում է խաղացողներին և ստուգում շրջափակումը
	int process_cell(t_map *map, int y, int x, int *player_count)
	{
		char c;

		c = get_char_at(map, y, x);
		if (c == '\0')
			c = ' ';
		if (!is_map_char(c))
		{
			fprintf(stderr, "Error\nInvalid map character '%c' at (%d,%d)\n", c,
				y, x);
			return (0);
		}
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			(*player_count)++;
			map->player_x = x;
			map->player_y = y;
			map->player_dir = c;
		}
		if (needs_enclosure(c))
		{
			if (!cell_enclosed(map, y, x))
			{
				fprintf(stderr, "Error\nMap cell at (%d,%d) is not enclosed\n",
					y, x);
				return (0);
			}
		}
		return (1);
	}
