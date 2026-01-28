#ifndef CUB3D_H
# define CUB3D_H

# include "../Libft/libft.h"
# include "mlx.h"
# include <fcntl.h>  // Ֆայլեր բացելու համար
# include <stdio.h>  // Տպելու և սխալների ֆունկցիաներ (printf, perror)
# include <stdlib.h> // Հիշողության և ելքի ֆունկցիաներ (malloc, free, exit)
# include <string.h> // Սխալի տողերը ստանալու համար (strerror)
# include <unistd.h> // Ֆայլի գործողություններ (close, read, write)

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_texture
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_texture;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_game
{
	t_texture	textures;
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
}				t_game;

typedef struct s_cub
{
	t_game		game;
	void		*mlx;
	void		*win;
}				t_cub;

typedef struct s_parser
{
	int			fd;
	char		*line;
	int			rd;
	char		**map_lines;
	int			map_count;
	int			in_map;
	char		*s;
	char		*t;
	int			parsed;
	char		*copy;
	char		**new;
	int			i;
	int			maxw;
	int			l;
}				t_parser;

void			free_str_array(char **arr);
int				parse_rgb(char *color_str, int *r, int *g, int *b);
int				is_map_char(char c);
int				needs_enclosure(char c);
int				cell_enclosed(t_map *map, int y, int x);
int				process_cell(t_map *map, int y, int x, int *player_count);

int				validate_textures(t_texture *textures);
int				validate_map(t_map *map);
int				validate_color(char *color_str, t_color *color);

int				parse_header_line(char *t, t_game *game);
int				append_map_line(t_parser *p, char *s);
void			compute_map_width(t_parser *p, t_game *game);
int				read_lines(t_parser *p, t_game *game);

int				parse_game(const char *path, t_game *game);

void			err(char *msg);
void			print_err(char *msg);
t_cub			*init_game(char *path);
void			free_cub(t_cub *cub);

#endif
