/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_walls_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 23:52:21 by otlacerd          #+#    #+#             */
/*   Updated: 2026/05/26 23:59:35 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	next_index_non_whitespace(char *string, int *index, int pre_increment)
{
	if (!string || !index)
		end_program("Invalid pointer in function 'next_non_whitespace'", 1);
	*index = 0;
	while(is_white_space(string[*index]))
		(*index)++;
	if (pre_increment == true)
		(*index)--;
	return (1);
}

int	last_index_non_whitespace(char *string, int *index)
{
	if (!string || !index)
		return (0);
	*index = string_length(string) - 1;
	while (*index > 0 && is_white_space(string[*index]))
		(*index)--;
	return (1);
}

int	next_ln_non_whitespace(char **map, int column, int *line, int pre_increment)
{
	if (!map || !line)
		return (0);
	(*line) = 0;
	while (map[*line] && is_white_space(map[*line][column]))
		(*line)++;
	if (pre_increment == true)
		(*line)--;
	return (1);
}

int	last_ln_non_wtspace(char **map, int column, int *line, int line_size)
{
	if (!map || !line)
		return (0);
	(*line) = line_size - 1;
	while (*line > 0 && is_white_space(map[*line][column]))
		(*line)--;
	return (1);
}