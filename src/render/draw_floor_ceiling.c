#include "cub3D.h"

static int	interpolate(int c1, int c2, double t)
{
	int	r;
	int	g;
	int	b;

	r = ((c1 >> 16) & 0xFF) * (1 - t)
		+ ((c2 >> 16) & 0xFF) * t;
	g = ((c1 >> 8) & 0xFF) * (1 - t)
		+ ((c2 >> 8) & 0xFF) * t;
	b = (c1 & 0xFF) * (1 - t)
		+ (c2 & 0xFF) * t;
	return ((r << 16) | (g << 8) | b);
}

void	draw_floor_ceiling(t_cub *cub, int x, int screen_h)
{
	t_floor_draw	d;

	d.top_color = 0x1B3B6F;
	d.horizon_color = 0x87CEEB;
	d.floor_color = color_to_int(cub->game.floor_color);
	d.y = 0;
	while (d.y < screen_h)
	{
		if (d.y < screen_h / 2)
		{
			d.t = (double)d.y / (screen_h / 2);
			d.color = interpolate(d.top_color, d.horizon_color, d.t);
		}
		else
			d.color = d.floor_color;
		img_pixel_put(&cub->img, x, d.y, d.color);
		d.y++;
	}
}
