/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 22:17:51 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/19 09:03:38 by otlacerd         ###   ########.fr       */
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

void	parse(t_all *all)
{
	if (all->argc != 2)
		end_program("Wrong argument count", 1);
	if (!check_map_type(all->maps->name))
		end_program("Wrong map type. Expected 'file.cub'.", 1);
	if (!create_map(all->maps))
		end_program("Failed to create_map in parse", 1);
	print_map(all->maps->file);
	if (!get_map_grid(all->maps, all->conf))
		end_program("Failed to get map_grip from file", 1);
	print_map(all->maps->map);
	if (!check_close_walls(all->maps->map))
		end_program("Map is not properly enclosed by walls '1'", 1);
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
