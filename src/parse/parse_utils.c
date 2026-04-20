/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 04:55:03 by olacerda          #+#    #+#             */
/*   Updated: 2026/04/20 06:02:01 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "parse.h"

int	adress_is_valid(char *adress)
{
	int fd;

	if (!adress)
		return (0);
	fd = open(adress, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

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
			set_config_content(string, conf->ref[line], conf);
			return (1);
		}
		line++;
	}
	return (0);
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
