#include "cub3D.h"

void	err(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	sys_err(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	print_err(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
