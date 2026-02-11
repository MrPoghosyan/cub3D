#include "cub3D.h"

double	ft_fabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	safe_cell(t_cub *cub, int y, int x)
{
	if (y < 0 || x < 0)
		return (0);
	if (y >= cub->game.map.height)
		return (0);
	if (x >= (int)ft_strlen(cub->game.map.grid[y]))
		return (0);
	return (cub->game.map.grid[y][x]);
}
