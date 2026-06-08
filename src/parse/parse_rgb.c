/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:23:53 by gustoliv          #+#    #+#             */
/*   Updated: 2026/06/08 17:15:38 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_next_number(char *string, int *index, char xar)
{
	int	color;
	int	count;

	if (!string || !xar || !index)
		return (-1);
	color = 0;
	count = 0;
	while (string[*index] && string[*index] != ',')
	{
		if (!is_numeric(string[*index]))
			end_program("Invalid input on RGB configuration (not numeric)", 1);
		color = (color * 10) + (string[*index] - 48);
		(*index)++;
		count++;
	}
	if (count > 3)
		return (-1);
	return (color);
}

int	get_element_color(char *string)
{
	int	index;
	int	count;
	int	color;
	int	number;

	index = 0;
	color = 0;
	count = -1;
	while (++count < 3 && string[index])
	{
		number = get_next_number(string, &index, ',');
		if (number < 0 || number > 255)
			end_program("Invalid number on RGB configuration", 1);
		color += number;
		if (string[index] == ',')
			++index;
		if (count < 2)
			color = color << RGB_BIT;
	}
	if (string[index] != '\0')
		return (end_program("Invalid configuration in RGB element", 1), -1);
	return (color);
}

int	parse_and_set_rgb(t_config *config)
{
	if (!config)
		return (0);
	config->color_f = get_element_color(config->f);
	if (config->color_f < 0)
		return (end_program("Invalid number on RGB element F", 1), 0);
	config->color_c = get_element_color(config->c);
	if (config->color_c < 0)
		return (end_program("Invalid number on RGB element C", 1), 0);
	return (1);
}
