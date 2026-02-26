#include "cub3D.h"

static void	load_gun_image(t_cub *cub, int index, char *path)
{
	int	width;
	int	height;

	cub->gun[index].img = mlx_xpm_file_to_image(cub->mlx, path, &width,
			&height);
	if (!cub->gun[index].img)
	{
		err("Couldn't open gun texture!\n");
	}
	cub->gun[index].addr = mlx_get_data_addr(cub->gun[index].img,
			&cub->gun[index].bits_per_pixel, &cub->gun[index].line_length,
			&cub->gun[index].endian);
}

void	set_gun_0_1(t_cub *cub)
{
	load_gun_image(cub, 0, "./textures/1.xpm");
	load_gun_image(cub, 1, "./textures/2.xpm");
}

void	set_gun_2_3(t_cub *cub)
{
	load_gun_image(cub, 2, "./textures/3.xpm");
	load_gun_image(cub, 3, "./textures/4.xpm");
}

void	set_gun_4(t_cub *cub)
{
	load_gun_image(cub, 4, "./textures/5.xpm");
}

void	set_guns(t_cub *cub)
{
	cub->gun = malloc(sizeof(t_img) * 5);
	if (!cub->gun)
	{
		free_cub(cub);
		err("Malloc error!\n");
	}
	ft_memset(cub->gun, 0, sizeof(t_img) * 5);
	set_gun_0_1(cub);
	set_gun_2_3(cub);
	set_gun_4(cub);
}
