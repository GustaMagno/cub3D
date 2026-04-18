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
	return (0);
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

int	create_img(t_mlx *mlx, t_img *img)
{
	img->height = 64;
	img->width = 64;
	img->bits_per_pixel = 32;
	img->img = mlx_new_image(mlx->mlx, img->width, img->height);
	if (!img->img)
		return (-1);
	img->adress = mlx_new_image(mlx->mlx, img->width, img->height);
	if (!img->img)
		return (-1);
	return (0);
}

int	put_color(t_img *img, int color)
{
	int	i;
	int	t_pixeis;

	i = 0;
	t_pixeis = img->height * img->width;
	while (i < t_pixeis)
	{
		((int *)img->adress)[i] = color;
		i += 4;
	}
}

int	mlx_exec(t_mlx *mlx)
{
	int error;

	error = 0;
	mlx->test_map = (char *[]){"111111",
							   "100001", 
							   "100001", 
							   "100001", 
							   "111111", NULL};
	error += create_img(mlx, mlx->blue_img);
	error += create_img(mlx, mlx->red_img);
	if (error < 0)
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
