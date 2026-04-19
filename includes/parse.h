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

#ifndef PARSING_H
# define PARSING_H
# include "utils.h"

//=====- parse.c -==============================================================
void	parse(t_all *all); //Do the whole parse of the project
int     check_map_type(char *map_name); //Verify if the map_file end with '.cub'
int     check_close_walls(char **map); //Verify if the map is surrounded by '1'

//=====- parse_utils.c -========================================================
int     is_valid(char xar); //Verify if it is one of the permitted characters
int     check_axis(char **map, int *line, int *column, int *axis);
int		get_grid_beginning(t_map *maps, t_config *conf); //Returns -1 when fails. Get the beginning of the 'map_grid' in raw_map
int		is_config(char *string, t_config *conf); // Verify if the 'string' argument is a configuration line of the chosen map file
char	**get_config_pointer(char *string, t_config *config);
int		get_config_content(char *string, char *config_element, t_config *config);

//=====- data_structure.c -=====================================================
int		create_map(t_map *maps); //Converts the whole 'chosen_file' to a char **
int		get_map_grid(t_map *maps, t_config *conf);// Gets the 'grid_map' compoused by '0's '1's inside the chosen map file
int		get_file_lines(char *map_name); //Return line count of the map
char	*get_map_adress(char *map_name); //Gets struct 'all' adress from any place

#endif
