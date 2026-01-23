#include "engine.h"

void draw_map_2d(t_cub *cub)
{
    int x, y;
    int size = 20; // մի բջիջի pixel չափը
    for (y = 0; y < cub->game.map.height; y++)
    {
        for (x = 0; x < cub->game.map.width; x++)
        {
            char c = cub->game.map.grid[y][x];
            int color;

            if (c == '1')
                color = 0xFFFFFF; // White wall
            else
                color = 0x000000; // Black floor

            int px = x * size;
            int py = y * size;

            // simple pixel fill (rectangle)
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    mlx_pixel_put(cub->mlx, cub->win, px + i, py + j, color);
        }
    }

    // Draw player
    int px = cub->game.map.player_x * size;
    int py = cub->game.map.player_y * size;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mlx_pixel_put(cub->mlx, cub->win, px + i, py + j, 0xFF0000); // Red player
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
