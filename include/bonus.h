#ifndef BONUS_H
# define BONUS_H

# include "struct.h"

void	minimap(t_cub *cub);
int		mouse_rot(int x, int y, t_cub *cub);
void	rot_left(t_cub *cub);
void	rot_right(t_cub *cub);
void	try_to_open_door(t_cub *cub);
void	set_guns(t_cub *cub);
void	set_gun_0_1(t_cub *cub);
void	set_gun_2_3(t_cub *cub);
void	set_gun_4(t_cub *cub);

#endif
