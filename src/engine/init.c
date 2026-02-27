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

static void	set_dir_ns(t_cub *cub, char d)
{
	if (d == 'N')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
		cub->player.plane_x = 0.66;
		cub->player.plane_y = 0;
	}
	else
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
	else
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
	if (d != 'N' && d != 'S' && d != 'E' && d != 'W')
	{
		printf("Warning: invalid player_dir '%c', using default 'N'\n", d);
		d = 'N';
	}
	if (d == 'N' || d == 'S')
		set_dir_ns(cub, d);
	else
		set_dir_ew(cub, d);
	if (cub->player.dir_x == 0 && cub->player.dir_y == 0)
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
	}
	if (cub->player.plane_x == 0 && cub->player.plane_y == 0)
	{
		cub->player.plane_x = 0.66;
		cub->player.plane_y = 0;
	}
}

void	ray_init(t_cub *cub, t_ray *ray, int x, int w)
{
	double	camera_x;

	camera_x = 2 * x / (double)w - 1;
	ray->ray_dir_x = cub->player.dir_x
		+ cub->player.plane_x * camera_x;
	ray->ray_dir_y = cub->player.dir_y
		+ cub->player.plane_y * camera_x;
	ray->map_x = (int)cub->player.x;
	ray->map_y = (int)cub->player.y;
	ray->delta_x = ft_fabs(1 / ray->ray_dir_x);
	ray->delta_y = ft_fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}
