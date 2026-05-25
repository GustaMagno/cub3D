#include "exec.h"

int		colision(t_mlx *mlx, double p_x, double p_y)
{
	int	x;
	int	y;

	x = (int)p_x / 64;
	y = (int)p_y / 64;
	if (mlx->all->maps->map[y][x] == '1')
		return (1);
	return (0);
}

void	rotate_player(t_ray *ray, double angle)
{
	double	old_dirX;
	double	old_planeX;

	old_dirX = ray->dirX;
	old_planeX = ray->planeX;
	ray->dirX = old_dirX * cos(angle) - ray->dirY * sin(angle);
	ray->dirY = old_dirX * sin(angle) + ray->dirY * cos(angle);
	ray->planeX = old_planeX * cos(angle) - ray->planeY * sin(angle);
	ray->planeY = old_planeX * sin(angle) + ray->planeY * cos(angle);
}

void	move_player(t_mlx *mlx, double speed, double x_move, double y_move)
{
	if ((mlx->k_d - mlx->k_a) == 1)
	{
		y_move += mlx->ray->dirX * speed;
		x_move += -mlx->ray->dirY * speed;
	}
	if ((mlx->k_d - mlx->k_a) == -1)
	{
		y_move += -mlx->ray->dirX * speed;
		x_move += mlx->ray->dirY * speed;
	}
	if (mlx->k_w - mlx->k_s == 1)
	{
		y_move += mlx->ray->dirY * speed;
		x_move += mlx->ray->dirX * speed;
	}
	if (mlx->k_w - mlx->k_s == -1)
	{
		y_move -= mlx->ray->dirY * speed;
		x_move -= mlx->ray->dirX * speed;
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
	move_player(mlx, 0.15, mlx->x_test, mlx->y_test);
	if (mlx->k_lrot == 1)
		rotate_player(mlx->ray, -0.005);
	if (mlx->k_rrot == 1)
		rotate_player(mlx->ray, 0.005);
	return (1);
}
