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
            img_pixel_put(&cub->img, x, y, 0x87CEEB); // ceiling
            y++;
        }
        x++;
    }
}
