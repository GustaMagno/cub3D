/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 22:17:51 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/20 05:59:29 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int	check_characters(t_map *maps)
{
	int	player_count;
	int	line;
	int	column;

	if (!maps)
		return (0);
	player_count = 0;
	line = 0;
	while (maps->map[++line])
	{
		column = -1;
		while (maps->map[line][++column])
		{
			if (maps->map[line][column] == 'N' || maps->map[line][column] == 'S'
				|| maps->map[line][column] == 'E' || maps->map[line][column] == 'W')
				player_count++;
			if (!is_valid(maps->map[line][column], true) || (player_count > 1))
				return (0);
		}
	}
	if (player_count < 1)
		return (0);
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
		if (!adress_is_valid(get_config_pointer(conf->ref[line], conf)))
			return (0);		
		line++;
	}
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
	print_map(all->maps->file);
	beginning = 0;
	if (!set_map_config(all->maps, all->conf, &beginning))
		end_program("Failed to set map_config", 1);
	if (!set_map_grid(all->maps, all->conf, beginning))
		end_program("Failed to set map_grip from file", 1);
	print_map(all->maps->map);
	if (!check_close_walls(all->maps->map))
		end_program("Map is not properly enclosed by walls '1'", 1);
	if (!check_characters(all->maps))
		end_program("Invalid set of characters in the map", 1);
	
	printf("all->conf->no ==  %s\n", all->conf->no);
	printf("all->conf->so ==  %s\n", all->conf->so);
	printf("all->conf->we ==  %s\n", all->conf->we);
	printf("all->conf->ea ==  %s\n", all->conf->ea);
	printf("all->conf->f ==  %s\n", all->conf->f);
	printf("all->conf->c ==  %s\n", all->conf->c);
	//if (!check_path) (flood fill)
	//if (!get_infos)
	//if (!check_characters) Letras proibidas, (validos / invalidos, quantidades, etc)
	//"normalizar" o mapa (colocar espacos pra ficar quadrado)
	//  // pra isso vai precisar da "quantidade de colunas", que e o tamanho da maior string da GRID
}
