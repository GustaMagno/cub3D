/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 22:17:51 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/21 18:41:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_map_type(char *map_name)
{
	int	name_size;
	char *type;
	int	type_size;

	if (!map_name)
		return (0);
	type = MAP_TYPE;
	type_size = string_length(type);
	name_size = string_length(map_name);
	if (name_size <= type_size)
		return (0);
	map_name += name_size - type_size;
	if (string_compare(map_name, type, 0) == 0)
		return (1);
	return (0);	
}

int	check_close_walls(char **map)
{
	int	line;
	int	column;

	if (!map)
		return (0);
	if (!check_axis(map, &line, &column, &line))
		return (0);
	if (!check_axis(map, &line, &column, &column))
		return (0);
	return (1);
}

int	check_characters(t_map *maps, t_play *play)
{
	int	player_count;
	int	line;
	int	column;

	if (!maps)
		return (0);
	player_count = 0;
	line = -1;
	while (maps->map[++line])
	{
		column = -1;
		while (maps->map[line][++column])
		{
			if ((maps->map[line][column] == 'N' || maps->map[line][column] == 'S'
				|| maps->map[line][column] == 'E' || maps->map[line][column] == 'W')
				&& player_count++)
				set_player_info(play, line, column, maps->map);
			if (!is_valid(maps->map[line][column], true) || (player_count > 1))
				return (print_errors((char *[]){"Invalid character \"",
					(char []){maps->map[line][column], '\0'}, "\" ", "in --> ", NULL},
						line, column, true), 0);
		}
	}
	if (player_count < 1)
		end_program("Missing player in the map", 1);
	return (1);
}

int	check_config_adresses(t_config *conf)
{
	int	line;

	if (!conf)
		return (0);
	line = 0;
	while (conf->ref[line])
	{
		if (!adress_is_valid(*(get_config_pointer(conf->ref[line], conf))))
			return (0);
		line++;
	}
	return (1);
}

void	parse(t_all *all)
{
	int	beginning;

	if (!all)
		end_program("Invalid pointer in function: parse", 1);
	if (all->argc != 2)
		end_program("Wrong argument count", 1);
	if (!check_map_type(all->maps->name))
		end_program("Wrong map type. Expected 'file.cub'.", 1);
	if (!create_map(all->maps))
		end_program("Failed to create_map in parse", 1);		
	beginning = 0;
	if (!set_map_config(all->maps, all->conf, &beginning))
		end_program("Failed to set map_config", 1);
	if (!check_config_adresses(all->conf))
		end_program("Invalid adress in map configuration", 1);
	if (!set_map_grid(all->maps, all->conf, beginning))
		end_program("Failed to set map_grip from file", 1);
	if (!check_characters(all->maps, all->play))
		end_program(NULL, 1);
	if (!check_close_walls(all->maps->map))
		end_program("Map is not properly enclosed by walls '1'", 1);
}
