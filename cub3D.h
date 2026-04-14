/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:53:26 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/14 23:09:17 by gustoliv         ###   ########.fr       */
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
# include "exec.h"
# include "defines.h"

typedef struct s_all
{
	int a;
}				t_all;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	size_t	tile_size;
	t_all	*all;
}				t_mlx;

#endif