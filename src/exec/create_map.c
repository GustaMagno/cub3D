#include "exec.h"

void	*conditional_img(t_mlx *mlx, char tale)
{
	if (tale == '1')
		return (mlx->red_img->adress);
	if (tale == '0')
		return (mlx->blue_img->adress);
	if (tale == 'N' || tale == 'S' || tale == 'E' || tale == 'W')
		return (mlx->blue_img->adress);
	return (mlx->blue_img->adress);
}

void	put_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*adress;

	adress = mlx->screen_img->adress + (y * mlx->screen_img->line_len
		+ x * (mlx->screen_img->bits_per_pixel / 8));
	*(unsigned int *)adress = color;
}

void	put_wall(t_mlx *mlx, int x, int wall_color)
{
	int		y;
	int		screen_h;
	double	line_height;
	double	draw_start;
	double	draw_end;

	y = -1;
	screen_h = mlx->all->maps->lines * 64;
	line_height = screen_h / mlx->ray->wall_dist;
	draw_start = screen_h / 2 - line_height / 2; 
	draw_end = screen_h / 2 + line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= screen_h)
		draw_end = screen_h - 1;
	wall_color = (0x8B8B8B * mlx->ray->side) + (0x5A5A5A * (mlx->ray->side == 0));
	while (++y < screen_h)
	{
		if (y < draw_start)
			put_pixel(mlx, x, y, 0x87CEEB);
		else if (y <= draw_end)
			put_pixel(mlx, x, y, wall_color);
		else
			put_pixel(mlx, x, y, 0x4A3728);
	}
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

void	dda_ray(t_mlx *mlx, t_ray *ray, double rayDirX, double rayDirY)
{
	ray->map_x = (int)(mlx->x_test / 64.0);
	ray->map_y = (int)(mlx->y_test / 64.0);
	ray->delta_dist_x = fabs(1.0 / rayDirX);
	ray->delta_dist_y = fabs(1.0 / rayDirY);
	dda_step_assign(mlx, ray, rayDirX, rayDirY);
	while (mlx->all->maps->map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
	if (ray->side == 0)
    	ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
    	ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void	put_map_in_buffer(t_mlx *mlx)
{
	int		x;
	int		screenW;
	double	cameraX;
	double	rayDirY;
	double	rayDirX;

	x = -1;
	screenW = mlx->all->maps->columns * 64;
	while (++x < screenW)
	{
		cameraX = 2.0 * x / screenW - 1;
		rayDirX = mlx->ray->dirX + mlx->ray->planeX * cameraX;
		rayDirY = mlx->ray->dirY + mlx->ray->planeY * cameraX;
		dda_ray(mlx, mlx->ray, rayDirX, rayDirY);
		put_wall(mlx, x, 0xFF0000);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_img->img, 0, 0);
}
