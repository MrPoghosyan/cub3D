#ifndef ENGINE_H
# define ENGINE_H

# include "cub3D.h"

/* ========= ENGINE ========= */
void	engine_init(t_cub *cub);
int		engine_loop(t_cub *cub);

/* ========= RENDER ========= */
void	render_frame(t_cub *cub);

/* ========= INPUT ========= */
int		key_press(int keycode, t_cub *cub);
int		close_game(t_cub *cub);

#endif
