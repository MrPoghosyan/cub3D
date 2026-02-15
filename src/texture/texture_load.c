#include "cub3D.h"

static int load_one(t_cub *cub, t_tex_img *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(cub->mlx,
            path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error\nFailed to load texture: %s\n", path);
        return (0);
    }

    tex->addr = (int *)mlx_get_data_addr(
            tex->img,
            &tex->bpp,
            &tex->line_len,
            &tex->endian);
    if (!tex->addr)
        return (0);
    return (1);
}

int load_textures(t_cub *cub)
{
    t_texture *t;

    t = &cub->game.textures;

    if (!load_one(cub, &t->no, t->no_path))
        return (0);
    if (!load_one(cub, &t->so, t->so_path))
        return (0);
    if (!load_one(cub, &t->we, t->we_path))
        return (0);
    if (!load_one(cub, &t->ea, t->ea_path))
        return (0);

    return (1);
}
