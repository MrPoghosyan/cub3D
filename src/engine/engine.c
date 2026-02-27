#include "cub3D.h"

void	engine_init(t_cub *cub)
{
	int	size;
	int	i;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		err("mlx_init failed");
	cub->win = mlx_new_window(cub->mlx, 1200, 800, "cub3D");
	if (!cub->win)
		err("mlx_new_window failed");
	cub->img.img = mlx_new_image(cub->mlx, 1200, 800);
	cub->img.addr = mlx_get_data_addr(cub->img.img,
			&cub->img.bits_per_pixel,
			&cub->img.line_length,
			&cub->img.endian);
	size = 800 * cub->img.line_length;
	i = -1;
	while (++i < size)
		cub->img.addr[i] = 0;
	mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
	mlx_hook(cub->win, 17, 0, close_game, cub);
	mlx_hook(cub->win, 6, 1L << 6, mouse_rot, cub);
	mlx_loop_hook(cub->mlx, engine_loop, cub);
	if (!load_textures(cub))
		err("Texture load failed");
}

void	render_frame(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);
	render_3d(cub);
}

int	engine_loop(t_cub *cub)
{
	render_3d(cub);
	minimap(cub);
	mlx_put_image_to_window(
		cub->mlx,
		cub->win,
		cub->img.img,
		0, 0);
	return (0);
}
