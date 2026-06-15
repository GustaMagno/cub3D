/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:38:52 by otlacerd          #+#    #+#             */
/*   Updated: 2026/06/15 17:38:52 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parse.h"

void	dir_assign(t_mlx *mlx, t_all *all)
{
	if (all->play->direction == NO)
	{
		mlx->ray->diry = -1;
		mlx->ray->planex = 0.66;
	}
	if (all->play->direction == SO)
	{
		mlx->ray->diry = 1;
		mlx->ray->planex = -0.66;
	}
	if (all->play->direction == EA)
	{
		mlx->ray->dirx = 1;
		mlx->ray->planey = 0.66;
	}
	if (all->play->direction == WE)
	{
		mlx->ray->dirx = -1;
		mlx->ray->planey = -0.66;
	}
}

int	mlx_assign(t_mlx *mlx, t_all *all)
{
	mlx->all = all;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, 1920, 1080, "cube3D");
	if (!mlx->win)
		return (free(mlx->mlx), 0);
	mlx->x_test = (mlx->all->play->column * 64) + 32;
	mlx->y_test = (mlx->all->play->line * 64) + 32;
	mlx->ray = ft_calloc(1, sizeof(t_ray));
	if (!mlx->ray)
		return (close_x(mlx), 0);
	mlx->screen_h = 1080;
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
	fill_structs(all, argc, argv, &mlx);
	parse(all);
	if (!mlx_assign(&mlx, all))
		return (1);
	if (!mlx_exec(&mlx))
		return (1);
	end_program(NULL, 0);
}
