#include "cub3D.h"

static void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

static void free_textures(t_cub *cub)
{
    t_texture *t;

    t = &cub->game.textures;

    /* free texture paths (malloc-ed strings) */
    if (t->no_path)
        free(t->no_path);
    if (t->so_path)
        free(t->so_path);
    if (t->we_path)
        free(t->we_path);
    if (t->ea_path)
        free(t->ea_path);

    /* destroy mlx images */
    if (t->no.img)
        mlx_destroy_image(cub->mlx, t->no.img);
    if (t->so.img)
        mlx_destroy_image(cub->mlx, t->so.img);
    if (t->we.img)
        mlx_destroy_image(cub->mlx, t->we.img);
    if (t->ea.img)
        mlx_destroy_image(cub->mlx, t->ea.img);
}

void free_cub(t_cub *cub)
{
    if (!cub)
        return;

    free_textures(cub);
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
