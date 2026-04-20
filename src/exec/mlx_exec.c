#include "exec.h"

int	key_handler(int keycode, void *mlx)
{
	t_mlx	*p;

	if (!mlx)
		return (0);
	p = (t_mlx *)mlx;
	if (keycode == ESC)
	{
		end_mlx(mlx);
		//end_structs(mlx->all);
		exit (1);
	}
	if (keycode == KEY_W)
		p->k_w = 1;
	if (keycode == KEY_A)
		p->k_a = 1;
	if (keycode == KEY_S)
		p->k_s = 1;
	if (keycode == KEY_D)
		p->k_d = 1;
	return (1);
}

int		key_release(int keycode, void *p)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)p;
	if (keycode == KEY_W)
		mlx->k_w = 0;
	if (keycode == KEY_A)
		mlx->k_a = 0;
	if (keycode == KEY_S)
		mlx->k_s = 0;
	if (keycode == KEY_D)
		mlx->k_d = 0;
	return (0);
}

t_img	*new_img(t_mlx *mlx, int width, int height)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->height = height;
	img->width = width;
	img->img = mlx_new_image(mlx->mlx, img->width, img->height);
	if (!img->img)
		return (NULL);
	img->adress = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_len, &img->endian);
	if (!img->img)
		return (NULL);
	return (img);
}

void	put_color(t_img *img, int color)
{
	int	i;
	int	t_pixeis;

	i = 0;
	t_pixeis = img->height * img->width;
	while (i < t_pixeis)
	{
		((int *)img->adress)[i] = color;
		i++;
	}
}

int	create_images(t_mlx *mlx)
{
	mlx->blue_img = new_img(mlx, 64, 64);
	if (!mlx->blue_img)
		return (0);
	mlx->red_img = new_img(mlx, 64, 64);
	if (!mlx->red_img)
		return (free(mlx->blue_img), 0);
	mlx->screen_img = new_img(mlx, 6 * 64, 5 * 64);
	if (!mlx->blue_img)
		return (free(mlx->blue_img), free(mlx->red_img), 0);
	return (1);
}

int	mlx_exec(t_mlx *mlx)
{
	int error;

	error = 0;
	mlx->test_map = (char *[]){"111111",
							   "101001", 
							   "100101", 
							   "110001", 
							   "111111", NULL};
	mlx->column_count = 6;
	if (!create_images(mlx))
		return (0);
	put_color(mlx->red_img, 0xFF0000);
	put_color(mlx->blue_img, 0x0000FF);
	mlx_hook(mlx->win, 2, 1L << 0, key_handler, mlx);
	mlx_hook(mlx->win, 17, 0, close_x, mlx);
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx);
	mlx_loop_hook(mlx->mlx, render_game, mlx);
	mlx_do_sync(mlx->mlx);
	return (mlx_loop(mlx->mlx));
}
