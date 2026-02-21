#include "cub3D.h"

void	rot_left(t_cub *cub)
{
	double	tmp;

	tmp = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(-0.05) - cub->player.dir_y
		* sin(-0.05);
	cub->player.dir_y = tmp * sin(-0.05) + cub->player.dir_y * cos(-0.05);
	tmp = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(-0.05) - cub->player.plane_y
		* sin(-0.05);
	cub->player.plane_y = tmp * sin(-0.05) + cub->player.plane_y * cos(-0.05);
}

void	rot_right(t_cub *cub)
{
	double	tmp;

	tmp = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(0.05) - cub->player.dir_y
		* sin(0.05);
	cub->player.dir_y = tmp * sin(0.05) + cub->player.dir_y * cos(0.05);
	tmp = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(0.05) - cub->player.plane_y
		* sin(0.05);
	cub->player.plane_y = tmp * sin(0.05) + cub->player.plane_y * cos(0.05);
}

void	try_to_open_door(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)cub->player.x + (int)cub->player.dir_x;
	y = (int)cub->player.y + (int)cub->player.dir_y;
	if (cub->game.map.grid[x][y] == 'C')
		cub->game.map.grid[x][y] = 'O';
	else if (cub->game.map.grid[x][y] == 'O')
		cub->game.map.grid[x][y] = 'C';
}

int	mouse_rot(int x, int y, t_cub *cub)
{
	static int	past_x;

	(void)y;
	if (x < past_x)
		rot_right(cub);
	else if (x > past_x)
		rot_left(cub);
	past_x = x;
	return (0);
}
