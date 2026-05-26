/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 23:49:27 by otlacerd          #+#    #+#             */
/*   Updated: 2026/05/26 23:59:35 by otlacerd         ###   ########.fr       */
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

int	closed_ends(char **map, int column_size, int line_size)
{
	int	end;
	int	beginning;
	int	line;
	int	index;

	if (!map)
		return (0);
	line = 0;
	while (map[line])
	{
		next_index_non_whitespace(map[line], &beginning, false);
		last_index_non_whitespace(map[line], &end);
		if (map[line][beginning] != '1' || map[line][end] != '1')
			return (0);
		line++;
	}
	index = -1;
	while (++index < column_size)
	{
		next_ln_non_whitespace(map, index, &beginning, false);
		last_ln_non_wtspace(map, index, &end, line_size);
		if (map[beginning][index] != '1' || map[end][index] != '1')
			return (0);
	}
	return (1);
}
