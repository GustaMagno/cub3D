#include "exec.h"

unsigned int	get_color(t_img *img, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(img->adress + (y * img->line_len
		+ x * (img->bits_per_pixel / 8)));
	return (color);
}

void	put_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*adress;

	adress = mlx->screen_img->adress + (y * mlx->screen_img->line_len
		+ x * (mlx->screen_img->bits_per_pixel / 8));
	*(unsigned int *)adress = color;
}

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
		if (mlx->ray->step_x > 0)
			wall_pointW = 1.0 - wall_pointW;
	}
	else
	{
		wall_pointW = (mlx->x_test / 64.0) + mlx->ray->wall_dist * rayDirX;
		wall_pointW -= floor(wall_pointW);
		if (mlx->ray->step_y < 0)
			wall_pointW = 1.0 - wall_pointW;
	}
	return (wall_pointW * 64);
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

void	draw_image(t_mlx *mlx, int x, double rayDirX, double rayDirY)
{
	int		y;
	int		screen_h;
	double	line_height;
	double	draw_start_real;
	double	draw_end_real;
	double	draw_start;
	double	draw_end;
	double	teste;

	y = -1;
	screen_h = mlx->all->maps->lines * 64;
	line_height = screen_h / mlx->ray->wall_dist;
	draw_start_real = screen_h / 2 - line_height / 2;
	draw_end_real   = screen_h / 2 + line_height / 2;
	draw_start = draw_start_real < 0 ? 0 : draw_start_real;
	draw_end   = draw_end_real >= screen_h ? screen_h - 1 : draw_end_real;
	mlx->wall_img = wall_img(mlx);
	teste = texture_pointW(mlx, rayDirX, rayDirY);
	while (++y < screen_h)
	{
		if (y < draw_start)
			put_pixel(mlx, x, y, 0x87CEEB);
		else if (y <= draw_end)
			put_pixel(mlx, x, y, wall_colorH(mlx->wall_img, teste,
				line_height, y - draw_start_real));
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
		draw_image(mlx, x, rayDirX, rayDirY);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_img->img, 0, 0);
}
