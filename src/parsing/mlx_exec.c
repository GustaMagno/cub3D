#include "cub3D.h"

t_mlx	*new_mlx(t_all *all)
{
    t_mlx	*mlx;

    mlx = ft_calloc(sizeof(t_mlx), 1);
    if (!mlx)
        return (NULL);
	mlx->tile_size = 32;
	mlx->all = all;
}

void	end_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx);
	free(mlx);
}

int	close_x(t_mlx *mlx)
{
	//end_structs(mlx->all);
	end_mlx(mlx);
	exit (1);
}

int	key_handler(int keycode, void *mlx)
{
	if (keycode == ESC)
	{
		end_mlx(mlx);
		//end_structs(mlx->all);
		exit (1);
	}
}

int	mlx_exec(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return (0);
	mlx->win = mlx_new_window(mlx, 800, 800, "cube3D");
	if (!mlx->win)
        return (0);
	mlx_hook(mlx->win, 17, 0, close_x, mlx);
	mlx_key_hook(mlx->win, key_handler, mlx);
	return (mlx_loop(mlx->mlx));
}