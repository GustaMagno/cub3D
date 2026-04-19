/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:53:26 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/19 08:17:16 by otlacerd         ###   ########.fr       */
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

# define DIR_NORTH "NO"
# define DIR_SOUTH "SO"
# define DIR_WEST  "WE"
# define DIR_EAST  "EA"
# define TEX_FLOOR "F"
# define TEX_CEIL  "C"

typedef unsigned long t_ul;

typedef enum s_lconf
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	END
}			t_lconf;

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

typedef struct s_config
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f;
	char *c;
	char *ref[7];
}				t_config;

typedef struct s_all
{
	t_map		*maps;
	t_config	*conf;
	int			argc;
	char		**argv;
}				t_all;


#endif