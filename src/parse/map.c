

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 22:23:07 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/17 18:18:17 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char *get_map_adress(char *map_name)
{
	char *full_adress;
	char *folder;
	int	append_necessity;

	if (!map_name)
		end_program("Invalid pointer in get_map_adress", 1);
	folder = MAPS_FOLDER;
	append_necessity = string_compare(map_name, folder, string_length(folder));
	if (append_necessity == false)
		return (map_name);
	full_adress = NULL;
	if (!string_appender(&full_adress, folder)
		|| !string_appender(&full_adress, map_name))
	{
		end_program("Failed string_appender in get_map_adress", 1);
	}
	return (full_adress);
}

int	set_map_grid(t_map *maps, t_config *conf, int beginning)
{
	int	line;

	if (!maps || !conf)
		return (0);
	maps->lines = array_string_length(maps->file + beginning);
	maps->columns = get_grid_columns(maps, beginning);
	if (maps->lines <= 0 || maps->columns <= 0)
		end_program("Invalid map proportion", 1);
	normalize_grid(maps, beginning);
	maps->map = malloc((maps->lines + 1) * sizeof(char *));
	if (!maps->map)
		end_program("Failed allocation of map in set_map_grid", 1);
	line = 0;
	while (maps->file[beginning] && (line < (maps->lines + 1)))
		maps->map[line++] = maps->file[beginning++];
	maps->map[line] = NULL;
	return (1);
}

int	create_map(t_map *maps)
{
	int	size;
	int	line;
	int	fd;

	if (!maps)
		return (0);
	maps->adress = get_map_adress(maps->name);
	size = get_file_lines(maps->adress);
	fd = open(maps->adress, O_RDONLY);
	if (fd < 0)
		return (end_program("Map not found, invalid fd in create_map", 1), 0);
	maps->file = malloc((size + 1) * sizeof(char *));
	if (!maps->file)
		return (end_program("Failed allocation in create_map", 1), 0);
	memory_zero(maps->file, size + 1, sizeof(*(maps->file)));
	line = -1;
	while (++line < size)
	{
		maps->file[line] = get_next_line_no_breakline(fd);
		if (!maps->file[line])
			break ;
	}
	trim_map_tail(maps->file);
	return (close(fd), 1);
}

int	get_file_lines(char *map_name)
{
	char *string;
	int	count;
	int	fd;

	if (!map_name)
		return (0);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (end_program("Map not found, invalid fd in get_file_lines", 1), 0);
	count = 0;
	string = " ";
	while (string != NULL)
	{
		string = get_next_line_no_breakline(fd);
		if (!string)
			break ;
		count++;
		free(string);
	}
	close(fd);
	return (count);
}

int	set_map_config(t_map *maps, t_config *config, int *beginning)
{
	int		w_spaces;
	int		line;
	int		count;

	if (!maps)
		end_program("Invalid pointer in set_map_grid", 1);
	count = 0;
	line = -1;
	while (maps->file[++line])
	{
		w_spaces = 0;
		while (is_white_space(maps->file[line][w_spaces]))
			w_spaces++;
		if (!maps->file[line][w_spaces])
			continue;
		if(!is_config(maps->file[line] + w_spaces, config))
		{
			if (count != config->count || !is_valid(maps->file[line][w_spaces], false))
			{
				printf("count: %d\n", count);
				end_program("Wrong configuration in map file", 1);
			}
			return (*beginning = line, 1);
		}
		count++;
	}
	return (0);
}
