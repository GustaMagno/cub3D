/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:23:53 by gustoliv          #+#    #+#             */
/*   Updated: 2026/06/09 13:09:37 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "parse.h"

int	get_next_number(char *string, int *index)
{
	int	color;
	int	count;

	if (!string || !index)
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
	if (count == 0)
		end_program("Empty number in RGB configuration", 1);
	if (string[*index] == ',')
		++(*index);
	if (count > 3)
		return (-1);
	return (color);
}

int	get_element_color(char *string)
{
	int	index;
	int	nbr_count;
	int	color;
	int	number;

	index = 0;
	color = 0;
	nbr_count = -1;
	while (++nbr_count < 3 && string[index])
	{
		number = get_next_number(string, &index);
		if (number < 0 || number > 255)
			end_program("Invalid number on RGB configuration", 1);
		color += number;
		if (nbr_count < 2)
			color = color << RGB_BIT;
	}
	if (nbr_count < 3)
		end_program("Empty number in RGB configuration", 1);
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
