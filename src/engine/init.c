#include "cub3D.h"

t_cub	*init_game(char *path)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		err("malloc failed");
	ft_memset(cub, 0, sizeof(t_cub));
	if (!parse_game(path, &cub->game))
	{
		free(cub);
		err("parse failed");
	}
	return (cub);
}

void	engine_init(t_cub *cub)
{
	int	size;
	int	i;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		err("mlx_init failed");
	cub->win = mlx_new_window(cub->mlx, 1200, 800, "cub3D");
	if (!cub->win)
		err("mlx_new_window failed");
	cub->img.img = mlx_new_image(cub->mlx, 1200, 800);
	cub->img.addr = mlx_get_data_addr(
			cub->img.img,
			&cub->img.bits_per_pixel,
			&cub->img.line_length,
			&cub->img.endian);
	size = 800 * cub->img.line_length;
	i = 0;
	while (i < size)
	{
		cub->img.addr[i] = 0;
		i++;
	}
	mlx_hook(cub->win, 2, 1L << 0, key_hook, cub); // ESC key
	mlx_hook(cub->win, 17, 0, close_game, cub);     // close window button
	mlx_loop_hook(cub->mlx, engine_loop, cub);
}

static void	set_dir_ns(t_cub *cub, char d)
{
	if (d == 'N')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
		cub->player.plane_x = 0.66;
		cub->player.plane_y = 0;
	}
	else // 'S'
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = 1;
		cub->player.plane_x = -0.66;
		cub->player.plane_y = 0;
	}
}

static void	set_dir_ew(t_cub *cub, char d)
{
	if (d == 'E')
	{
		cub->player.dir_x = 1;
		cub->player.dir_y = 0;
		cub->player.plane_x = 0;
		cub->player.plane_y = 0.66;
	}
	else //'W'
	{
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
		cub->player.plane_x = 0;
		cub->player.plane_y = -0.66;
	}
}

void	init_player(t_cub *cub)
{
	char	d;

	cub->player.x = cub->game.map.player_x + 0.5;
	cub->player.y = cub->game.map.player_y + 0.5;

	d = cub->game.map.player_dir;

	if (d == 'N' || d == 'S')
		set_dir_ns(cub, d);
	else
		set_dir_ew(cub, d);
}

void    ray_init(t_cub *cub, t_ray *ray, int x, int w)
{
    double  camera_x;

    camera_x = 2 * x / (double)w - 1;
    ray->ray_dir_x = cub->player.dir_x +
        cub->player.plane_x * camera_x;
    ray->ray_dir_y = cub->player.dir_y +
        cub->player.plane_y * camera_x;
    ray->map_x = (int)cub->player.x;
    ray->map_y = (int)cub->player.y;
    ray->delta_x = ft_fabs(1 / ray->ray_dir_x);
    ray->delta_y = ft_fabs(1 / ray->ray_dir_y);
    ray->hit = 0;
}

