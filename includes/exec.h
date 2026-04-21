#ifndef EXEC_H
# define EXEC_H

#include "cub3D.h"

void			*ft_calloc(size_t nmemb, size_t size);
int				mlx_exec(t_mlx *mlx);
int				mlx_assign(t_mlx *mlx, t_all *all);
int				render_game(void *p);
void			end_mlx(t_mlx *mlx);
int				close_x(t_mlx *mlx);
void			put_map_in_buffer(t_mlx *mlx);

#endif