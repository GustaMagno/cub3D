/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 04:55:03 by olacerda          #+#    #+#             */
/*   Updated: 2026/04/19 11:20:40 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_valid(char xar, int w_spaces)
{
	char *valid;
	int	index;

	if (!xar)
		return (0);
	if (w_spaces == false)
		valid = VALID_CHARACTERS;
	else
		valid = VALID_CHARACTERS_W_SPACE;
	index = 0;
	while (valid[index])
	{
		if (xar == valid[index])
			return (1);
		index++;
	}
	return (0);
}

char **get_config_pointer(char *string, t_config *config)
{
	if (!string || !config)
		return (NULL);
	else if (string_compare(string, config->ref[NO], 0) == 0)
		return (&(config->no));
	else if (string_compare(string, config->ref[SO], 0) == 0)
		return (&(config->so));
	else if (string_compare(string, config->ref[WE], 0) == 0)
		return (&(config->we));
	else if (string_compare(string, config->ref[EA], 0) == 0)
		return (&(config->ea));
	else if (string_compare(string, config->ref[F], 0) == 0)
		return (&(config->f));
	else if (string_compare(string, config->ref[C], 0) == 0)
		return (&(config->c));
	return (NULL);
}

int	get_config_content(char *string, char *config_element, t_config *config)
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
	(*element) = malloc((string_length(string) + 1) * sizeof(char));
	if (!(*element))
		end_program("Failed allocation in get_config_content", 1);
	index = -1;
	while (string[++index])
		(*element)[index] = string[index];
	(*element)[index] = '\0';
	return (1);
}

int	is_config(char *string, t_config *conf)
{
	int	line;

	if (!string || !conf)
		return (0);
	line = 0;
	while (conf->ref[line])
	{
		if (string_compare(string, conf->ref[line], string_length(conf->ref[line])) == 0)
		{
			get_config_content(string, conf->ref[line], conf);
			return (1);
		}
		line++;
	}
	return (0);
}


int	get_grid_beginning(t_map *maps, t_config *config)
{
	int		w_spaces;
	int		line;

	if (!maps)
		end_program("Invalid pointer in get_map_grid", 1);
	line = 0;
	while (maps->file[line])
	{
		w_spaces = 0;
		while (is_white_space(maps->file[line][w_spaces]))
			w_spaces++;
		if (!is_config(maps->file[line] + w_spaces, config) && is_valid(maps->file[line][w_spaces], false))
			return (line);
		line++;
	}
	return (FAIL);
}

//descondensar essa função em 2 mais simples. (repetir código, por legibilidade)
int	check_axis(char **map, int *line, int *column, int *axis)
{
	(*line) = -1;
	while (map[++(*line)])
	{
		(*column) = 0;
		while (map[(*line)][(*column)])
		{
			if (is_valid(map[(*line)][(*column)], false))
			{
				if ((map[(*line)][(*column)] != '1') &&  ++(*axis))
                    return (0);
				while (map[(*line)] && is_valid(map[(*line)][(*column)], false))
                    (*axis)++;
				if ((--(*axis) >= 0) && map[(*line)][(*column)] != '1')
                    return (0);
			}
            (void)((axis == line) && ++(*axis));
            if ((axis == line) && map[(*line)] && map[(*line)][(*column)])
                continue ;
            (void)((++(*column)) && (axis == line) && (*axis = 0));
		}
		if (axis == line)
			return (1);
	}
	return (1);
}
