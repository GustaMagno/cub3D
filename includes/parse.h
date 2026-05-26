/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:44:36 by gustoliv          #+#    #+#             */
/*   Updated: 2026/05/26 21:47:58 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "utils.h"

void	parse(t_all *all);
int		check_map_type(char *map_name);
int		check_close_walls(char **map);
int		check_characters(t_map *maps, t_play *play);
int		check_config_adresses(t_config *conf);
int		parse_and_set_rgb(t_config *config);
int		get_element_color(char *string);
int		get_next_number(char *string, int *index, char xar);

int		adress_is_valid(char *adress);
int		is_valid(char xar, int w_spaces);
int		is_config(char *string, t_config *conf);
int		check_axis(char **map, int *line, int *column, int *axis);
int		set_player_info(t_play *player, int line, int column, char **map);

int		normalize_grid(t_map *maps, int beginning);
int		set_conf_content(char *string, char *config_element, t_config *config);
char	**get_config_pointer(char *string, t_config *config);
int		trim_map_tail(char **map);
int		fix_padding_n_whitespaces(char *string, int size, int column_size);
int		get_grid_columns(char **map, int beginning);

int		create_map(t_map *maps);
int		set_map_config(t_map *maps, t_config *conf, int *beginning);
int		set_map_grid(t_map *maps, t_config *conf, int beginning);
int		get_file_lines(char *map_name);
char	*get_map_adress(char *map_name);

void	init_structs(t_all **all);
int		create_all_images(t_mlx *mlx, t_config *conf);
t_all	*get_all_reference(t_all *all);
int		fill_structs(t_all *all, int argc, char **argv, t_mlx *mlx);
int		fill_config(t_config *conf);

#endif
