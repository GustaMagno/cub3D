#include "exec.h"


int	render_game(void *p)
{
	t_mlx	*mlx;

	if (!p)
		return (0);
	mlx = (t_mlx *)p;
	put_map_in_buffer(mlx);
	if ((mlx->k_d - mlx->k_a) == 1)
		mlx->x_test += 0.2;
	if ((mlx->k_d - mlx->k_a) == -1)
		mlx->x_test -= 0.2;
	if (mlx->k_w - mlx->k_s == 1)
		mlx->y_test -= 0.2;
	if (mlx->k_w - mlx->k_s == -1)
		mlx->y_test += 0.2;
	return (1);
}
