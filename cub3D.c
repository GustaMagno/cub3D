#include "cub3D.h"
#include "exec.h"

int	mlx_assign(t_mlx *mlx, t_all *all)
{
	mlx->all = all;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, 800, 800, "cube3D");
	if (!mlx->win)
        return (free(mlx->mlx), 0);
	mlx->x_test = 100;
	mlx->y_test = 0;
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all	*all = NULL;
	static t_mlx	*mlx;

	if (!mlx_assign(mlx, all))
		return (1);
	if (!mlx_exec(mlx))
		return (1);
	(void) argc;
	(void) argv;
	(void) all;
}