#ifndef STRUCT_H
# define STRUCT_H

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
	int		hit;
	int		side;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
}	t_ray;

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

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_game		game;
	t_player	player;
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

#endif
