#include "exec.h"

void	*conditional_img(t_mlx *mlx, char tale)
{
	if (tale == '1')
		return (mlx->red_img->adress);
	if (tale == '0')
		return (mlx->blue_img->adress);
	return (mlx->blue_img->adress);
}

void	put_pixel(t_mlx *mlx, char *pixeis, int y, int x)
{
	int		i;
	int		j;
	size_t	line_pixeis;
	size_t	i_pixel;

	i = 0;
	line_pixeis = mlx->screen_img->line_len / (mlx->screen_img->bits_per_pixel / 8);
	i_pixel = (line_pixeis * y * 64) + (x * 64);
	while (i < 64)
	{
		j = -1;
		while (++j < 64)
			((int *)mlx->screen_img->adress)[i_pixel++] = ((int *)pixeis)[j];
		i_pixel += (line_pixeis - (line_pixeis / mlx->all->maps->lines));
		i++;
	}

}
//(mlx->column_count * y * 64 * 64) = Pula ate a coluna que quer iterar em pixeis, coluna vezes numero de linhas 
//(x * 64) = agora vai para o offset que quer começar a iteracao

void	put_map_in_buffer(t_mlx *mlx)
{
	int	y;
	int	x;

	y = -1;
	while (mlx->all->maps->map[++y])
	{
		x = -1;
		while (mlx->all->maps->map[y][++x])
			put_pixel(mlx, conditional_img(mlx, mlx->all->maps->map[y][x]), y, x);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen_img->img, 50, 50);
}
