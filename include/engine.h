#ifndef ENGINE_H
# define ENGINE_H

# define TILE_SIZE 20  // 1 map 20x20 pixels
# define PLAYER_SIZE 10
# define MOVE_SPEED 0.1
//# define ROT_SPEED 0.05
# define COS_R 0.99875026039   // cos(0.05)
# define SIN_R 0.04997916927   // sin(0.05)


/* ========== INIT ========== */
void	engine_init(t_cub *cub);
t_cub	*init_game(char *path);
void	init_player(t_cub *cub);
void    ray_init(t_cub *cub, t_ray *ray, int x, int w);

/* ========= ENGINE ========= */
int		engine_loop(t_cub *cub);
void	render_frame(t_cub *cub);

/* ========= RENDER ========= */
void	render_3d(t_cub *cub);
void	draw_player(t_cub *cub);

/* ========= INPUT ========== */
int		key_hook(int keycode, t_cub *cub);
int		close_game(t_cub *cub);

/* ========= MOVE 3D ======== */
void	move_forward(t_cub *cub);
void	move_backward(t_cub *cub);
void	move_left(t_cub *cub);
void	move_right(t_cub *cub);
void	turn_left(t_cub *cub);
void	turn_right(t_cub *cub);

/* ========= UTILS ========== */
void	clear_image(t_cub *cub, int w, int h);
void	img_pixel_put(t_img *img, int x, int y, int color);

#endif
