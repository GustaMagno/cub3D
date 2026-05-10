#include "exec.h"
#include "parse.h"

void	dir_assign(t_mlx *mlx, t_all *all)
{
	if (all->play->direction == NO)
	{
		mlx->ray->dirY = -1;
		mlx->ray->planeX = 0.66;
	}
	if (all->play->direction == SO)
	{
		mlx->ray->dirY = 1;
		mlx->ray->planeX = -0.66;
	}
	if (all->play->direction == EA)
	{
		mlx->ray->dirX = 1;
		mlx->ray->planeY = 0.66;
	}
	if (all->play->direction == WE)
	{
		mlx->ray->dirX = -1;
		mlx->ray->planeY = -0.66;
	}
}

int	mlx_assign(t_mlx *mlx, t_all *all)
{
	mlx->all = all;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, all->maps->columns * 64, all->maps->lines * 64, "cube3D");
	if (!mlx->win)
        return (free(mlx->mlx), 0);
	mlx->x_test = 10 * 64;
	mlx->y_test = 2 * 64;
	mlx->ray = ft_calloc(1, sizeof(t_ray));
	if (!mlx->ray)
        return (free(mlx->mlx), free(mlx->win), 0);
	dir_assign(mlx, all);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all			*all;
	static t_mlx	mlx;

	all = NULL;
	init_structs(&all);
	fill_structs(all, argc, argv);
	parse(all);
	if (!mlx_assign(&mlx, all))
		return (1);
	if (!mlx_exec(&mlx))
		return (1);
	end_program(NULL, 0);
}