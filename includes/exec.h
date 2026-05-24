#ifndef EXEC_H
# define EXEC_H

#include "cub3D.h"

void			dda_step_assign(t_mlx *mlx, t_ray *ray, double rayDirX, double rayDirY);
void			put_pixel(t_mlx *mlx, int x, int y, unsigned int color);
unsigned int	get_color(t_img *img, int x, int y);
t_img			*wall_img(t_mlx *mlx);
void			*ft_calloc(size_t nmemb, size_t size);
int				mlx_exec(t_mlx *mlx);
int				mlx_assign(t_mlx *mlx, t_all *all);
int				render_game(void *p);
void			end_mlx(t_mlx *mlx);
int				close_x(t_mlx *mlx);
void			put_map_in_buffer(t_mlx *mlx);
void			assign_draw(t_mlx *mlx, double d_rs, double d_re);

#endif