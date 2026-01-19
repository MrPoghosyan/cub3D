#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>    //open.
# include <math.h>     //math functions.
# include <stdio.h>    //printf, perror.
# include <stdlib.h>   //malloc, free, exit.
# include <string.h>   //strerror.
# include <sys/time.h> //gettimeofday.
# include <unistd.h>   //close, read, write.

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct s_texture
{
	char 	*no; // hyusis
	char 	*so; // haraf
	char 	*we; // arevmutq
	char 	*ea; // arevelq
}						t_texture;

typedef struct s_map
{
	char				**grid;
	int					width;
	int					height;
	int					player_x;
	int					player_y;
	char				player_dir;
}						t_map;

typedef struct s_game
{
	t_texture			textures;
	t_color				floor_color;
	t_color				ceiling_color;
	t_map				map;
	void				*mlx;
	void				*window;
}						t_game;

typedef struct s_all	t_all;

int						validate_color(char *color_str, t_color *color);
int						validate_textures(t_texture *textures);
int						validate_map(t_map *map);
int						parse_game(const char *path, t_game *game);

#endif
