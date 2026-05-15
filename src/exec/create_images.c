#include "exec.h"
#include "utils.h"

int	create_all_images(t_mlx *mlx, t_config *conf)
{
	if (!mlx || !conf)
		return (0);
	mlx->so = new_file_img(mlx->mlx, conf->so);
	mlx->no = new_file_img(mlx->mlx, conf->no);
	mlx->we = new_file_img(mlx->mlx, conf->we);
	mlx->ea = new_file_img(mlx->mlx, conf->ea);
	if (!mlx->so || !mlx->no || !mlx->we || !mlx->ea)
		return (end_program(
			"Error\n"
			"Failed to load texture images.\n"
			"Check texture paths and XPM files.", 1), 0);
	return (1);
}

t_img *new_file_img(void *mlx, char *adress)
{
	t_img *img;

	if (!adress)
		return (NULL);
	img = malloc (sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx, adress, WIDTH, HEIGHT);
	if (!img->img)
		return (NULL);
	img->adress = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_len, &img->endian);
	if (!img->adress)	
		return (NULL);
	img->height = HEIGHT;
	img->line_len = WIDTH;
	return (img);
}
