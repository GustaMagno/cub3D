/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:01:16 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/14 21:57:32 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "utils.h"

//=====- parse.c -==============================================================
void	parse(t_all *all); //Do the whole parse of the project
int     check_map_type(char *map_name); //Verify if the map_file end with '.cub'
int     check_close_walls(char **map); //Verify if the map is surrounded by '1'
int		check_characters(t_map *maps, t_play *play); //Verify all characters.
int     check_config_adresses(t_config *conf); //Verify all config adresses

//=====- parse_utils.c -========================================================
int     adress_is_valid(char *adress); //Check if open(adress) returns a valid FD.
int     is_valid(char xar, int w_spaces); //Check if 'xar' is allowed on the map. Set 'w_spaces' true to include white spaces.
int		is_config(char *string, t_config *conf); // Verify if the 'string' argument is a configuration of the chosen map file
int     check_axis(char **map, int *line, int *column, int *axis); //Check if an specific axis set by "*axis", begin all parts of the map with '1', and end with '1'.
int		set_player_info(t_play *player, int line, int column, char **map); //Set direction, line and column of the player.

//=====- map_utils.c -==================================================
int     normalize_grid(t_map *maps, int beginning); // Make all lines have the same size. (Same as the biggest one).
int		set_config_content(char *string, char *config_element, t_config *config); //Saves the content of an specific configuration "string".
char	**get_config_pointer(char *string, t_config *config); //Return the adress of an specific configuration pointer "string".
int     trim_map_tail(char **map); //Cut white_spaces at the end of all lines in map.
int     fix_padding_n_whitespaces(char *string, int size, int column_size); //Switch all white_spaces for 'space', and add spaces to smaller lines in order to be equal as the biggest one.
int		get_grid_columns(char **map, int beginning); // Count the size of the biggest string.

//=====- map.c -=====================================================
int		create_map(t_map *maps); //Converts the whole 'chosen_file' to a char **
int		set_map_config(t_map *maps, t_config *conf, int *beginning); //Returns -1 when fails. Get the beginning of the 'map_grid' in raw_map
int		set_map_grid(t_map *maps, t_config *conf, int beginning);// Gets the 'grid_map' compoused by '0's '1's inside the chosen map file
int		get_file_lines(char *map_name); //Return line count of the map
char	*get_map_adress(char *map_name); //Gets struct 'all' adress from any place

//=====- data_structure.c -===============================================================
void	init_structs(t_all **all);//Mallocs and sets '0' all structs of the project
t_all	*get_all_reference(t_all *all);//Returns 'all' adress when arg is NULL
int		fill_structs(t_all *all, int argc, char **argv);//Used at beginning of main
int		fill_config(t_config *conf); //Initialize struct 'config' variables.

#endif
