#include "cub3D.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 1200 || y >= 800)
		return ;
	dst = img->addr + (y * img->line_length + x *
			(img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int color_to_int(t_color c)
{
    return ((c.r & 0xFF) << 16) |
           ((c.g & 0xFF) << 8)  |
           (c.b & 0xFF);
}

void	clear_image(t_cub *cub, int w, int h)
{
    int x;
    int y;

    x = 0;
    while (x < w)
    {
        y = 0;
        while (y < h)
        {
            img_pixel_put(&cub->img, x, y,
                    color_to_int(cub->game.ceiling_color)); // ceiling
            y++;
        }
        x++;
    }
}

double  my_floor(double x)
{
    int i;

    i = (int)x;
    if (x < 0 && x != i)
        return (i - 1);
    return (i);
}
