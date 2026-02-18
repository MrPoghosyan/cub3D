#ifndef ASSETS_H
# define ASSETS_H

void	free_str_array(char **arr);
int		parse_rgb(char *color_str, int *r, int *g, int *b);
int		is_map_char(char c);
int		needs_enclosure(char c);
int		cell_enclosed(t_map *map, int y, int x);
int		process_cell(t_map *map, int y, int x, int *player_count);
int		validate_textures(t_texture *textures);
int		validate_map(t_map *map);
int		validate_color(char *color_str, t_color *color);
int		parse_header_line(char *t, t_game *game);
char	*str_trim_left(char *s);
int		append_map_line(t_parser *p, char *s);
void	compute_map_width(t_parser *p, t_game *game);
int		read_lines(t_parser *p, t_game *game);
int		init_parser_and_game(const char *path, t_parser *p, t_game *game);
int		setup_map(t_parser *p, t_game *game);
int		parse_game(const char *path, t_game *game);
void	err(char *msg);
void	print_err(char *msg);
void	free_cub(t_cub *cub);
double	ft_fabs(double n);
int		safe_cell(t_cub *cub, int y, int x);

#endif
