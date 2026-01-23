#ifndef ENGINE_H
# define ENGINE_H

# include "cub3D.h"

# define TILE_SIZE 20  // 1 map 20x20 pixels
# define PLAYER_SIZE 10
# define MOVE_SPEED 1
# define DEBUG_2D 1 //debug version

/* ========= ENGINE ========= */
void	engine_init(t_cub *cub);
int		engine_loop(t_cub *cub);

/* ========= RENDER ========= */
void	render_frame(t_cub *cub);
void	draw_map_2d(t_cub *cub); //begug for delled
void	draw_player(t_cub *cub);

/* ========= INPUT ========= */
int		key_hook(int keycode, t_cub *cub);
int		close_game(t_cub *cub);

/* ========= MOVE 2D ========= */
void	move_forward(t_cub *cub);
void	move_backward(t_cub *cub);
void	turn_left(t_cub *cub);
void	turn_right(t_cub *cub);

#endif
