#include "engine.h"

static void	draw_rect(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(cub->mlx, cub->win, x + j, y + i, color);
			++j;
		}
		++i;
	}
}

void	draw_map_2d(t_cub *cub)
{
	int y, x;
	int px, py;
	t_map *map = &cub->game.map;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			px = x * TILE_SIZE;
			py = y * TILE_SIZE;
			char c = map->grid[y][x];

			if (c == '1')          // Wall
				draw_rect(cub, px, py, 0x808080); // grey
			else if (c == '0')     // Empty floor
				draw_rect(cub, px, py, 0x000000); // black
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				draw_rect(cub, px, py, 0x000000); // piayer will be drawn later
			++x;
		}
		++y;
	}
}

void	draw_player(t_cub *cub)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = cub->game.map.player_x * TILE_SIZE + TILE_SIZE / 2;
	py = cub->game.map.player_y * TILE_SIZE + TILE_SIZE / 2;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			mlx_pixel_put(cub->mlx, cub->win, px - PLAYER_SIZE /2 +j, py - PLAYER_SIZE /2 +i, 0xFF0000); // red
																				j++;
		}
		i++;
	}
}

void	render_frame(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);

#if DEBUG_2D
	draw_map_2d(cub);
	draw_player(cub);
#else
	//render_3d_frame(cub);
#endif
}
