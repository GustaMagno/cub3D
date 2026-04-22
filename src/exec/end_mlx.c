#include "exec.h"
#include "parse.h"

void	free_img(t_img *img, t_mlx *mlx)
{
	if (img)
	{
		if (img->img)
			mlx_destroy_image(mlx->mlx, img->img);
		free(img);
	}
}

void	end_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		free_img(mlx->red_img, mlx);
		free_img(mlx->blue_img, mlx);
		free_img(mlx->screen_img, mlx);
		free_img(mlx->player_img, mlx);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
}

int	close_x(t_mlx *mlx)
{
	end_program(NULL, 0);
	end_mlx(mlx);
	exit (1);
}
