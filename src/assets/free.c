/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalieyan <natalieyan@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by natalieyan        #+#    #+#             */
/*   Updated: 2026/02/21 21:11:22 by natalieyan       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

static void	free_textures(t_cub *cub)
{
	t_texture	*t;

	t = &cub->game.textures;
	if (t->no_path)
		free(t->no_path);
	if (t->so_path)
		free(t->so_path);
	if (t->we_path)
		free(t->we_path);
	if (t->ea_path)
		free(t->ea_path);
	if (t->no.img)
		mlx_destroy_image(cub->mlx, t->no.img);
	if (t->so.img)
		mlx_destroy_image(cub->mlx, t->so.img);
	if (t->we.img)
		mlx_destroy_image(cub->mlx, t->we.img);
	if (t->ea.img)
		mlx_destroy_image(cub->mlx, t->ea.img);
}

#ifdef __linux__
static void	free_mlx_display(void *mlx)
{
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
}
#else
static void	free_mlx_display(void *mlx)
{
	(void)mlx;
}
#endif

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	free_textures(cub);
	free_map(&cub->game.map);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	free_mlx_display(cub->mlx);
	free(cub);
}
