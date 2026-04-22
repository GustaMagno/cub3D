/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:53:26 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/22 16:45:33 by gustoliv         ###   ########.fr       */
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
# include <stdbool.h>
# include "mlx.h"

# define FAIL -1
# define BUFFER_SIZE 25

# define SUBJECT_ERROR "Error\n"
# define MAPS_FOLDER "assets/maps/"
# define MAP_TYPE ".cub"
# define VALID_CHARACTERS "01NSEW"
# define VALID_CHARACTERS_W_SPACE "01NSEW 	"

# define DIR_NORTH "NO"
# define DIR_SOUTH "SO"
# define DIR_WEST  "WE"
# define DIR_EAST  "EA"
# define TEX_FLOOR "F"
# define TEX_CEIL  "C"

typedef unsigned long t_ul;

typedef enum s_dir
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	END
}			t_dir;

typedef struct s_gnl
{
	int		start;
	int		end;
	int		readbytes;
}				t_gnl;


typedef	struct s_map
{
	char	**file;
	char	**map;
	char	*name;
	char	*adress;
	int		lines;
	int		columns;
}				t_map;

typedef struct s_play
{
	int		line;
	int		column;
	t_dir	direction;
}				t_play;

typedef struct s_config
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f;
	char *c;
	char *ref[7];
	int	count;
}				t_config;

typedef struct s_all
{
	t_map		*maps;
	t_config	*conf;
	t_play		*play;
	int			argc;
	char		**argv;
}				t_all;

# define ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define UP    65362
# define DOWN  65364
# define LEFT  65361
# define RIGHT 65363

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
	t_img	*player_img;
	t_all	*all;
}				t_mlx;

#endif