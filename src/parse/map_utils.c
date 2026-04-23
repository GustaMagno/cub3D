/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 05:57:25 by olacerda          #+#    #+#             */
/*   Updated: 2026/04/23 10:47:27 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "parse.h"

int	get_grid_columns(char **map, int beginning)
{
	int	result;
	int	size;
	int	line;

	if (!map)
		end_program("Invalid pointer in get_grid_columns", 1);
	line = beginning;
	result = 0;
	while (map[line])
	{
		size = string_length(map[line]);
		if (size > result)
			result = size;
		line++;
	}
	return (result);
}

int	normalize_grid(t_map *maps, int beginning)
{
	int	size;
	int	line;

	if (!maps)
		return (0);	
	line = beginning;
	while (maps->file[line])
	{
		size = string_length(maps->file[line]);
		if (size < maps->columns)
		{
			maps->file[line] = re_allocker(maps->file[line], size, maps->columns + 1, sizeof(*(maps->file[line])));
			fix_padding_n_whitespaces(maps->file[line], size, maps->columns);		
		}
		line++;
	}
	return (1);
}

int	set_config_content(char *string, char *config_element, t_config *config)
{
	char **element;
	int	index;

	if (!string || !config_element || !config)
		return (0);
	index = 0;
	while (*string == config_element[index++])
		string++;
	while (is_white_space(*string))
		string++;
	element = get_config_pointer(config_element, config);
	if (*element)
		end_program("Repeated identifier in map configuration", 1);
	(*element) = malloc((string_length(string) + 1) * sizeof(char));
	if (!(*element))
		end_program("Failed allocation in set_config_content", 1);
	index = -1;
	while (string[++index])
		(*element)[index] = string[index];
	(*element)[index] = '\0';
	return (1);
}

char **get_config_pointer(char *string, t_config *config)
{
	if (!string || !config)
		return (NULL);
	if (string_compare(string, config->ref[NO], 0) == 0)
		return (&(config->no));
	if (string_compare(string, config->ref[SO], 0) == 0)
		return (&(config->so));
	if (string_compare(string, config->ref[WE], 0) == 0)
		return (&(config->we));
	if (string_compare(string, config->ref[EA], 0) == 0)
		return (&(config->ea));
	if (string_compare(string, config->ref[F], 0) == 0)
		return (&(config->f));
	if (string_compare(string, config->ref[C], 0) == 0)
		return (&(config->c));
	return (NULL);
}

int	trim_map_tail(char **map)
{
	int	line;
	int	index;

	if (!map)
		return (0);
	line = 0;
	while (map[line])
	{
		index = string_length(map[line]);
		while ((index > 0) && is_white_space(map[line][index - 1]))
		{
			map[line][index - 1] = '\0';
			index--;
		}
		line++;
	}
	return (1);
}

int	fix_padding_n_whitespaces(char *string, int size, int column_size)
{
	int	index;

	if (!string)
		return (0);
	index = 0;
	while (((size > 0) && (index < size)) || string[index])
	{
		if (is_white_space(string[index]))
			string[index] = ' ';
		index++;
	}
	while (index < column_size)
		string[index++] = ' ';
	return (1);
}
