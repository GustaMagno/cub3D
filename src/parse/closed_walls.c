/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:41:08 by otlacerd          #+#    #+#             */
/*   Updated: 2026/06/15 17:41:09 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_lines(char **map)
{
	int	line;
	int	column;

	if (!map)
		return (0);
	line = 0;
	while (map[line])
	{
		column = 0;
		while (map[line][column])
		{
			if (is_valid(map[line][column], false))
			{
				if (map[line][column] != '1')
					return (0);
				while (map[(line)] && is_valid(map[line][column], false))
					column++;
				if ((--column >= 0) && map[line][column] != '1')
					return (0);
			}
			column++;
		}
		line++;
	}
	return (1);
}

int	check_columns(char **map)
{
	int	line;
	int	column;

	if (!map || !(*map))
		return (0);
	column = -1;
	line = 0;
	while (map[line] && map[line][++column])
	{
		while (map[line] && map[line][column])
		{
			if (is_valid(map[line][column], false))
			{
				if (map[line][column] != '1')
					return (0);
				while (map[(line)] && is_valid(map[line][column], false))
					line++;
				if ((--line >= 0) && map[line] && map[line][column] != '1')
					return (0);
			}
			line++;
		}
		line = 0;
	}
	return (1);
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
