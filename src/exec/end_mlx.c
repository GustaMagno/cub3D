/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 19:47:46 by gustoliv          #+#    #+#             */
/*   Updated: 2026/05/26 22:48:41 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parse.h"

void	free_img(t_img *img, t_mlx *mlx)
{
	if (img)
	{
		if (img->img)
			mlx_destroy_image(mlx->mlx, img->img);
		free(img);
	}
}

void	end_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		free_img(mlx->screen_img, mlx);
		free_img(mlx->so, mlx);
		free_img(mlx->no, mlx);
		free_img(mlx->we, mlx);
		free_img(mlx->ea, mlx);
		mlx_destroy_display(mlx->mlx);
		free(mlx->ray);
		free(mlx->mlx);
	}
}

int	close_x(t_mlx *mlx)
{
	end_mlx(mlx);
	end_program(NULL, 0);
	exit (1);
}
