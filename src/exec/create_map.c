#include "exec.h"

unsigned int	wall_colorH(t_img *img, double wall_W, int wallH, int y)
{
	double	percent_H;

	percent_H = (double) y / wallH;
	percent_H *= 64;
	return (get_color(img, (int)wall_W, (int)percent_H));
}

double	texture_pointW(t_mlx *mlx, double rayDirX, double rayDirY)
{
	double	wall_pointW;

	if (mlx->ray->side == 0)
	{
		wall_pointW = (mlx->y_test / 64.0) + mlx->ray->wall_dist * rayDirY;
		wall_pointW -= floor(wall_pointW);
	}
	else
	{
		wall_pointW = (mlx->x_test / 64.0) + mlx->ray->wall_dist * rayDirX;
		wall_pointW -= floor(wall_pointW);	
	}
	return (wall_pointW * 64);
}

void	draw_image(t_mlx *mlx, int x, double rayDirX, double rayDirY)
{
	int		y;
	double	line_height;
	double	draw_start_real;
	double	draw_end_real;
	double	texture_W;

	y = -1;
	line_height = mlx->screen_h / mlx->ray->wall_dist;
	draw_start_real = mlx->screen_h / 2 - line_height / 2;
	draw_end_real = mlx->screen_h / 2 + line_height / 2;
	assign_draw(mlx, draw_start_real, draw_end_real);
	texture_W = texture_pointW(mlx, rayDirX, rayDirY);
	while (++y < mlx->screen_h)
	{
		if (y < mlx->draw_start)
			put_pixel(mlx, x, y, 0x87CEEB);
		else if (y <= mlx->draw_end)
			put_pixel(mlx, x, y, wall_colorH(mlx->wall_img, texture_W,
				line_height, y - draw_start_real));
		else
			put_pixel(mlx, x, y, 0x4A3728);
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
		draw_image(mlx, x, rayDirX, rayDirY);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_img->img, 0, 0);
}
