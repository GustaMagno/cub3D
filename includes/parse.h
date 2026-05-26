/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:01:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/05/27 00:01:35 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "utils.h"

//=====- parse.c -==============================================================
void	parse(t_all *all); //Do the whole parse of the project
int     check_map_type(char *map_name); //Verify if the map_file end with '.cub'
int     check_close_walls(char **map, int column_size, int line_size); //Verify
int		check_characters(t_map *maps, t_play *play); //Verify all characters.
int     check_config_adresses(t_config *conf); //Verify all config adresses
int		parse_and_set_rgb(t_config *config);
int		get_element_color(char *string);
int		get_next_number(char *string, int *index, char xar);

//====- closed_walls.c -========================================================
int		closed_ends(char **map, int column_size, int line_size);
int		check_columns(char **map);
int		check_lines(char **map);

//====- closed_walls_utils.c -=================================================
int		next_index_non_whitespace(char *string, int *index, int pre_increment); 
int		next_ln_non_whitespace(char **map, int column, int *line, int pre_inc);
int		last_index_non_whitespace(char *string, int *index);
int		last_ln_non_wtspace(char **map, int column, int *line, int line_size);

//=====- parse_utils.c -=======================================================
int     adress_is_valid(char *adress);
int     is_valid(char xar, int w_spaces);
int		is_config(char *string, t_config *conf);
int     check_axis(char **map, int *line, int *column, int *axis);
int		set_player_info(t_play *player, int line, int column, char **map);

//=====- map_utils.c -=================================================
int     normalize_grid(t_map *maps, int beginning);
int		set_conf_content(char *string, char *config_element, t_config *config);
char	**get_config_pointer(char *string, t_config *config);
int     trim_map_tail(char **map);
int     fix_padding_n_whitespaces(char *string, int size, int column_size);
int		get_grid_columns(char **map, int beginning); // Count the size of the bi

//=====- map.c -====================================================
int		create_map(t_map *maps);
int		set_map_config(t_map *maps, t_config *conf, int *beginning);
int		set_map_grid(t_map *maps, t_config *conf, int beginning);
int		get_file_lines(char *map_name);
char	*get_map_adress(char *map_name);

//=====- data_structure.c -=====================================================
void	init_structs(t_all **all);
int		create_all_images(t_mlx *mlx, t_config *conf);
t_all	*get_all_reference(t_all *all);
int		fill_structs(t_all *all, int argc, char **argv, t_mlx *mlx);
int		fill_config(t_config *conf);

#endif
