#include "cub3D.h"

void	draw_square(double i, double j, t_cub *cub, int color)
{
	int	k;
	int	l;

	k = (i * 10) - 5;
	while (k < (i * 10) + 5)
	{
		l = (j * 10) - 5;
		while (l < (j * 10) + 5)
		{
			img_pixel_put(&cub->img, l + 10, k + 10, color);
			l++;
		}
		k++;
	}
}

static void	init_color(t_color *col, int r, int g, int b)
{
	col->r = r;
	col->g = g;
	col->b = b;
}

static int	get_tile_color(char tile, t_color *col)
{
	if (tile == '1')
		init_color(col, 0, 0, 0);
	else if (tile == '0' || ft_strchr("NSEW", tile))
		init_color(col, 153, 204, 255);
	else if (tile == 'C')
		init_color(col, 0, 204, 204);
	else if (tile == 'O')
		init_color(col, 102, 255, 178);
	else
		return (0);
	return (1);
}

void	minimap(t_cub *cub)
{
	int		i;
	int		j;
	t_color	col;

	i = -1;
	while (++i < cub->game.map.height && cub->game.map.grid[i])
	{
		j = -1;
		while (++j < (int)ft_strlen(cub->game.map.grid[i])
			&& cub->game.map.grid[i][j])
		{
			if (get_tile_color(cub->game.map.grid[i][j], &col))
				draw_square(i, j, cub, color_to_int(col));
		}
	}
	col.r = 255;
	col.g = 255;
	col.b = 0;
	draw_square(cub->player.y - 0.5, cub->player.x - 0.5, cub,
		color_to_int(col));
}
