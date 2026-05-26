/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 19:44:54 by gustoliv          #+#    #+#             */
/*   Updated: 2026/05/26 19:44:54 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	colision(t_mlx *mlx, double p_x, double p_y)
{
	int	x;
	int	y;

	x = (int)(p_x) / 64;
	y = (int)(p_y) / 64;
	if (mlx->all->maps->map[y][x] == '1')
		return (1);
	x = (int)(p_x + 2) / 64;
	y = (int)(p_y + 2) / 64;
	if (mlx->all->maps->map[y][x] == '1')
		return (1);
	x = (int)(p_x - 2) / 64;
	y = (int)(p_y - 2) / 64;
	if (mlx->all->maps->map[y][x] == '1')
		return (1);
	x = (int)(p_x + 2) / 64;
	y = (int)(p_y - 2) / 64;
	if (mlx->all->maps->map[y][x] == '1')
		return (1);
	x = (int)(p_x - 2) / 64;
	y = (int)(p_y + 2) / 64;
	if (mlx->all->maps->map[y][x] == '1')
		return (1);
	return (0);
}

void	rotate_player(t_ray *ray, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = ray->dirx;
	old_planex = ray->planex;
	ray->dirx = old_dirx * cos(angle) - ray->diry * sin(angle);
	ray->diry = old_dirx * sin(angle) + ray->diry * cos(angle);
	ray->planex = old_planex * cos(angle) - ray->planey * sin(angle);
	ray->planey = old_planex * sin(angle) + ray->planey * cos(angle);
}

void	move_player(t_mlx *mlx, double speed, double x_move, double y_move)
{
	if ((mlx->k_d - mlx->k_a) == 1)
	{
		y_move += mlx->ray->dirx * speed;
		x_move += -mlx->ray->diry * speed;
	}
	if ((mlx->k_d - mlx->k_a) == -1)
	{
		y_move += -mlx->ray->dirx * speed;
		x_move += mlx->ray->diry * speed;
	}
	if (mlx->k_w - mlx->k_s == 1)
	{
		y_move += mlx->ray->diry * speed;
		x_move += mlx->ray->dirx * speed;
	}
	if (mlx->k_w - mlx->k_s == -1)
	{
		y_move -= mlx->ray->diry * speed;
		x_move -= mlx->ray->dirx * speed;
	}
	if (colision(mlx, x_move, y_move))
		return ;
	mlx->x_test = x_move;
	mlx->y_test = y_move;
}

int	render_game(void *p)
{
	t_mlx	*mlx;

	if (!p)
		return (0);
	mlx = (t_mlx *)p;
	put_map_in_buffer(mlx);
	move_player(mlx, 3, mlx->x_test, mlx->y_test);
	if (mlx->k_lrot == 1)
		rotate_player(mlx->ray, -0.04);
	if (mlx->k_rrot == 1)
		rotate_player(mlx->ray, 0.04);
	return (1);
}
