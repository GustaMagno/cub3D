/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 19:54:30 by gustoliv          #+#    #+#             */
/*   Updated: 2026/05/27 00:06:15 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

t_img	*new_file_img(void *mlx, char *adress)
{
	t_img	*img;

	if (!adress)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx, adress, &img->width, &img->height);
	if (!img->img)
		return (free(img), NULL);
	img->adress = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	if (!img->adress)
		return (free(img), mlx_destroy_image(mlx, img->img), NULL);
	return (img);
}

int	create_all_images(t_mlx *mlx, t_config *conf)
{
	if (!mlx || !conf)
		return (0);
	mlx->so = new_file_img(mlx->mlx, conf->so);
	mlx->no = new_file_img(mlx->mlx, conf->no);
	mlx->we = new_file_img(mlx->mlx, conf->we);
	mlx->ea = new_file_img(mlx->mlx, conf->ea);
	if (!mlx->so || !mlx->no || !mlx->we || !mlx->ea)
		return (printf("Error\n"), printf("Failed to load texture images.\n"),
			printf("Check texture paths and XPM files."), close_x(mlx), 0);
	return (1);
}
