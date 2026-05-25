#include "exec.h"

unsigned int	get_color(t_img *img, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(img->adress + (y * img->line_len
		+ x * (img->bits_per_pixel / 8)));
	return (color);
}

void	assign_draw(t_mlx *mlx, double d_rs, double d_re)
{
	if (d_rs < 0)
		mlx->draw_start = 0;
	else
		mlx->draw_start = d_rs;
	if (d_re >= mlx->screen_h)
		mlx->draw_end = mlx->screen_h - 1;
	else
		mlx->draw_end = d_re;
	mlx->wall_img = wall_img(mlx);
}

void	put_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*adress;

	adress = mlx->screen_img->adress + (y * mlx->screen_img->line_len
		+ x * (mlx->screen_img->bits_per_pixel / 8));
	*(unsigned int *)adress = color;
}


t_img	*wall_img(t_mlx *mlx)
{
	if (mlx->ray->side == 0)
	{
		if (mlx->ray->step_x > 0)
			return (mlx->ea);
		else
			return(mlx->we);
	}
	if (mlx->ray->step_y > 0)
		return (mlx->so);
	return (mlx->no);
	
}

void	dda_step_assign(t_mlx *mlx, t_ray *ray, double rayDirX, double rayDirY)
{
	double pos_x;
	double pos_y;

	pos_x = mlx->x_test / 64.0;
	pos_y = mlx->y_test / 64.0;
	if (rayDirX < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - pos_x) * ray->delta_dist_x;
	}
	if (rayDirY < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - pos_y) * ray->delta_dist_y;
	}
}
