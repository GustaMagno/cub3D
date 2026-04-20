#include "exec.h"

void	end_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
}

int	close_x(t_mlx *mlx)
{
	//end_structs(mlx->all);
	end_mlx(mlx);
	exit (1);
}
