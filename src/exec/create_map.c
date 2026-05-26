/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 19:53:05 by gustoliv          #+#    #+#             */
/*   Updated: 2026/05/26 19:53:05 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

unsigned int	wall_colorh(t_img *img, double wall_W, int wallH, int y)
{
	double	percent_h;

	percent_h = (double) y / wallH;
	percent_h *= 64;
	return (get_color(img, (int)wall_W, (int)(percent_h + 0.4)));
}

double	texture_pointw(t_mlx *mlx, double raydirx, double raydiry)
{
	double	wall_pointw;

	if (mlx->ray->side == 0)
	{
		wall_pointw = (mlx->y_test / 64.0) + mlx->ray->wall_dist * raydiry;
		wall_pointw -= floor(wall_pointw);
	}
	else
	{
		wall_pointw = (mlx->x_test / 64.0) + mlx->ray->wall_dist * raydirx;
		wall_pointw -= floor(wall_pointw);
	}
	return (wall_pointw * 64);
}

void	draw_image(t_mlx *mlx, int x, double raydirx, double raydiry)
{
	int		y;
	double	line_height;
	double	draw_start_real;
	double	draw_end_real;
	double	texture_w;

	y = -1;
	line_height = mlx->screen_h / mlx->ray->wall_dist;
	draw_start_real = mlx->screen_h / 2 - line_height / 2;
	draw_end_real = mlx->screen_h / 2 + line_height / 2;
	assign_draw(mlx, draw_start_real, draw_end_real);
	texture_w = texture_pointw(mlx, raydirx, raydiry);
	while (++y < mlx->screen_h)
	{
		if (y < draw_start_real)
			put_pixel(mlx, x, y, mlx->all->conf->color_c);
		else if (y <= mlx->draw_end)
			put_pixel(mlx, x, y, wall_colorh(mlx->wall_img, texture_w,
					line_height, y - draw_start_real));
		else
			put_pixel(mlx, x, y, mlx->all->conf->color_f);
	}
}

void	dda_ray(t_mlx *mlx, t_ray *ray, double raydirx, double raydiry)
{
	ray->map_x = (int)(mlx->x_test / 64.0);
	ray->map_y = (int)(mlx->y_test / 64.0);
	ray->delta_dist_x = fabs(1.0 / raydirx);
	ray->delta_dist_y = fabs(1.0 / raydiry);
	dda_step_assign(mlx, ray, raydirx, raydiry);
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
	int		screenw;
	double	camerax;
	double	raydiry;
	double	raydirx;

	x = -1;
	screenw = 1920;
	while (++x < screenw)
	{
		camerax = 2.0 * x / screenw - 1;
		raydirx = mlx->ray->dirx + mlx->ray->planex * camerax;
		raydiry = mlx->ray->diry + mlx->ray->planey * camerax;
		dda_ray(mlx, mlx->ray, raydirx, raydiry);
		draw_image(mlx, x, raydirx, raydiry);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_img->img, 0, 0);
}
