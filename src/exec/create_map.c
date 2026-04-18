#include "exec.h"

void	*conditional_img(t_mlx *mlx, char tale)
{
	if (tale == '1')
		return (mlx->red_img->img);
	if (tale == '0')
		return (mlx->blue_img->img);
}

void	put_pixel(t_mlx *mlx, void *pixeis, int i, int j)
{
	size_t	i_pixel;

	i_pixel = (i * 64);
}

void	put_map_in_buffer(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (mlx->test_map[++i])
	{
		j = 0;
		while (mlx->test_map[i][j])
			put_pixel(mlx, conditional_img(mlx, mlx->test_map[i][j++]), i, j);
	}
}
