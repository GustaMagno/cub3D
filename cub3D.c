
#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_all	*all;
	t_mlx	*mlx;

	mlx = new_mlx(all);
	if (!mlx)
		return (1);
	if (!mlx_exec(mlx))
		return (1);
	(void) argc;
	(void) argv;
	(void) all;
}