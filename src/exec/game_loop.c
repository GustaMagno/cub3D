#include "exec.h"


int	render_game(void *p)
{
	t_mlx	*mlx;

	if (!p)
		return (0);
	mlx = (t_mlx *)p;
	put_map_in_buffer(mlx);
	if ((mlx->k_d - mlx->k_a) == 1)
		mlx->x_test += 0.001;
	if ((mlx->k_d - mlx->k_a) == -1)
		mlx->x_test -= 0.001;
	if (mlx->k_w - mlx->k_s == 1)
		mlx->y_test -= 0.001;
	if (mlx->k_w - mlx->k_s == -1)
		mlx->y_test += 0.001;
	printf("PRESS X : %d, y : %d\n", (mlx->k_d - mlx->k_a), (mlx->k_w - mlx->k_s));
	mlx_pixel_put(mlx->mlx, mlx->win, mlx->x_test - 90, mlx->y_test + 50, 0xFF0000);
	return (1);
}
