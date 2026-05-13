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

//void	put_pixel(t_mlx *mlx, char *pixeis, int y, int x)
//{
//	int		i;
//	int		j;
//	size_t	line_pixeis;
//	size_t	i_pixel;
//
//	i = 0;
//	line_pixeis = mlx->screen_img->line_len / (mlx->screen_img->bits_per_pixel / 8);
//	i_pixel = (line_pixeis * y) + (x);
//	while (i < 64)
//	{
//		j = -1;
//		while (++j < 64)
//			((int *)mlx->screen_img->adress)[i_pixel++] = ((int *)pixeis)[j];
//		i_pixel += (line_pixeis - (line_pixeis / mlx->all->maps->columns));
//		i++;
//	}
//}

// void	put_map_in_buffer(t_mlx *mlx)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (mlx->all->maps->map[++y])
// 	{
// 		x = -1;
// 		while (mlx->all->maps->map[y][++x])
// 			put_pixel(mlx, conditional_img(mlx, mlx->all->maps->map[y][x]), y * 64, x * 64);
// 	}
// 	put_pixel(mlx, mlx->player_img->adress, mlx->y_test, mlx->x_test);
// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_img->img, 0, 0);
// }

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
	screen_h = (mlx->all->maps->lines * 64);
	line_height = screen_h / mlx->ray->wall_dist;
	draw_start = screen_h / 2 - line_height / 2; 
	draw_end = screen_h / 2 + line_height / 2; 
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= screen_h)
		draw_end = screen_h - 1;
	wall_color = (0xAA0000 * mlx->ray->side) + (0xFF0000 * (mlx->ray->side == 0));
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
	if (rayDirX < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (mlx->x_test - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - mlx->x_test) * ray->delta_dist_x;
	}
	if (rayDirY < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (mlx->y_test - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - mlx->y_test) * ray->delta_dist_y;
	}
}

void	dda_ray(t_mlx *mlx, t_ray *ray, double rayDirX, double rayDirY)
{
	ray->map_x = mlx->x_test / 64;
	ray->map_y = mlx->y_test / 64;
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
	// put_pixel(mlx, mlx->player_img->adress, mlx->y_test, mlx->x_test);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_img->img, 0, 0);
}
