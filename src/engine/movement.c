#include "cub3D.h"

static int	is_walkable(t_cub *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (0);
	if (map_y >= cub->game.map.height)
		return (0);
	if (map_x >= (int)ft_strlen(cub->game.map.grid[map_y]))
		return (0);
	return (cub->game.map.grid[map_y][map_x] != '1');
}

void	move_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x + cub->player.dir_x * MOVE_SPEED;
	new_y = cub->player.y + cub->player.dir_y * MOVE_SPEED;
	if (is_walkable(cub, new_x, cub->player.y))
		cub->player.x = new_x;
	if (is_walkable(cub, cub->player.x, new_y))
		cub->player.y = new_y;
}

void	move_backward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x - cub->player.dir_x * MOVE_SPEED;
	new_y = cub->player.y - cub->player.dir_y * MOVE_SPEED;
	if (is_walkable(cub, new_x, cub->player.y))
		cub->player.x = new_x;
	if (is_walkable(cub, cub->player.x, new_y))
		cub->player.y = new_y;
}

void	move_left(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x - cub->player.plane_x * MOVE_SPEED;
	new_y = cub->player.y - cub->player.plane_y * MOVE_SPEED;
	if (is_walkable(cub, new_x, cub->player.y))
		cub->player.x = new_x;
	if (is_walkable(cub, cub->player.x, new_y))
		cub->player.y = new_y;
}

void	move_right(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x + cub->player.plane_x * MOVE_SPEED;
	new_y = cub->player.y + cub->player.plane_y * MOVE_SPEED;
	if (is_walkable(cub, new_x, cub->player.y))
		cub->player.x = new_x;
	if (is_walkable(cub, cub->player.x, new_y))
		cub->player.y = new_y;
}

void	turn_right(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	cub->player.dir_x = cub->player.dir_x * COS_R - cub->player.dir_y * SIN_R;
	cub->player.dir_y = old_dir_x * SIN_R + cub->player.dir_y * COS_R;
	cub->player.plane_x = cub->player.plane_x * COS_R - cub->player.plane_y
		* SIN_R;
	cub->player.plane_y = old_plane_x * SIN_R + cub->player.plane_y * COS_R;
}

void	turn_left(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	cub->player.dir_x = cub->player.dir_x * COS_R + cub->player.dir_y * SIN_R;
	cub->player.dir_y = -old_dir_x * SIN_R + cub->player.dir_y * COS_R;
	cub->player.plane_x = cub->player.plane_x * COS_R + cub->player.plane_y
		* SIN_R;
	cub->player.plane_y = -old_plane_x * SIN_R + cub->player.plane_y * COS_R;
}
