#include "cub3D.h"

void	move_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x + cub->player.dir_x * MOVE_SPEED;
	new_y = cub->player.y + cub->player.dir_y * MOVE_SPEED;
	if (cub->game.map.grid[(int)cub->player.y][(int)new_x] != '1')
		cub->player.x = new_x;
	if (cub->game.map.grid[(int)new_y][(int)cub->player.x] != '1')
		cub->player.y = new_y;
}

void	move_backward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x - cub->player.dir_x * MOVE_SPEED;
	new_y = cub->player.y - cub->player.dir_y * MOVE_SPEED;
	if (cub->game.map.grid[(int)cub->player.y][(int)new_x] != '1')
		cub->player.x = new_x;
	if (cub->game.map.grid[(int)new_y][(int)cub->player.x] != '1')
		cub->player.y = new_y;
}

void    move_left(t_cub *cub)
{
    double  new_x;
    double  new_y;

    new_x = cub->player.x - cub->player.plane_x * MOVE_SPEED;
    new_y = cub->player.y - cub->player.plane_y * MOVE_SPEED;
    if (cub->game.map.grid[(int)cub->player.y][(int)new_x] != '1')
        cub->player.x = new_x;
    if (cub->game.map.grid[(int)new_y][(int)cub->player.x] != '1')
        cub->player.y = new_y;
}

void    move_right(t_cub *cub)
{
    double  new_x;
    double  new_y;

    new_x = cub->player.x + cub->player.plane_x * MOVE_SPEED;
    new_y = cub->player.y + cub->player.plane_y * MOVE_SPEED;
    if (cub->game.map.grid[(int)cub->player.y][(int)new_x] != '1')
        cub->player.x = new_x;
    if (cub->game.map.grid[(int)new_y][(int)cub->player.x] != '1')
        cub->player.y = new_y;
}

void turn_right(t_cub *cub)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = cub->player.dir_x;
    old_plane_x = cub->player.plane_x;

    cub->player.dir_x = cub->player.dir_x * COS_R - cub->player.dir_y * SIN_R;
    cub->player.dir_y = old_dir_x * SIN_R + cub->player.dir_y * COS_R;

    cub->player.plane_x = cub->player.plane_x * COS_R - cub->player.plane_y * SIN_R;
    cub->player.plane_y = old_plane_x * SIN_R + cub->player.plane_y * COS_R;
}

void turn_left(t_cub *cub)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = cub->player.dir_x;
    old_plane_x = cub->player.plane_x;

    cub->player.dir_x = cub->player.dir_x * COS_R + cub->player.dir_y * SIN_R;
    cub->player.dir_y = -old_dir_x * SIN_R + cub->player.dir_y * COS_R;

    cub->player.plane_x = cub->player.plane_x * COS_R + cub->player.plane_y * SIN_R;
    cub->player.plane_y = -old_plane_x * SIN_R + cub->player.plane_y * COS_R;
}
