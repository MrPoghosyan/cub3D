#include "cub3D.h"

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map->grid)
		return;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

static void	free_textures(t_texture *t)
{
	if (t->no)
		free(t->no);
	if (t->so)
		free(t->so);
	if (t->we)
		free(t->we);
	if (t->ea)
		free(t->ea);
}

void	free_cub(t_cub *cub)
{
	if (!cub)
		return;
	free_textures(&cub->game.textures);
	free_map(&cub->game.map);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
#ifdef __linux__
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
#endif
	free(cub);
}
