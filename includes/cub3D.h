/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:53:26 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/19 19:22:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>

# define ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define UP    65362
# define DOWN  65364
# define LEFT  65361
# define RIGHT 65363

typedef struct s_all
{
	int a;
}				t_all;

typedef struct s_img
{
	void	*img;
	char	*adress;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		k_w;
	int		k_a;
	int		k_s;
	int		k_d;
	int		column_count;
	double	x_test;
	double	y_test;
	char	**test_map;
	t_img	*screen_img;
	t_img	*red_img;
	t_img	*blue_img;
	t_all	*all;
}				t_mlx;

#endif