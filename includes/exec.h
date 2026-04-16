#ifndef EXEC_H
# define EXEC_H

typedef struct s_mlx t_mlx;
typedef struct s_all t_all;

void	*ft_calloc(size_t nmemb, size_t size);
int		mlx_exec(t_mlx *mlx);
t_mlx	*new_mlx(t_all *all);

#endif