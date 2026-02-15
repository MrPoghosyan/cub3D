#ifndef TEXTURE_H
# define TEXTURE_H

int			load_textures(t_cub *cub);
int			get_tex_pixel(t_tex_img *tex, int x, int y);
t_tex_img	*select_texture(t_cub *cub, t_ray *ray);

#endif
