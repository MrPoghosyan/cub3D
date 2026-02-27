#include "cub3D.h"

void	turn_right(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	cub->player.dir_x = cub->player.dir_x * COS_R
		- cub->player.dir_y * SIN_R;
	cub->player.dir_y = old_dir_x * SIN_R
		+ cub->player.dir_y * COS_R;
	cub->player.plane_x = cub->player.plane_x * COS_R
		- cub->player.plane_y * SIN_R;
	cub->player.plane_y = old_plane_x * SIN_R
		+ cub->player.plane_y * COS_R;
}

void	turn_left(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	old_plane_x = cub->player.plane_x;
	cub->player.dir_x = cub->player.dir_x * COS_R
		+ cub->player.dir_y * SIN_R;
	cub->player.dir_y = -old_dir_x * SIN_R
		+ cub->player.dir_y * COS_R;
	cub->player.plane_x = cub->player.plane_x * COS_R
		+ cub->player.plane_y * SIN_R;
	cub->player.plane_y = -old_plane_x * SIN_R
		+ cub->player.plane_y * COS_R;
}
