/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:01:04 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/19 00:34:27 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*re_allocker(void *pointer, t_ul size, t_ul new_size, t_ul type_size)
{
	char	*result;
	char	*string;
	t_ul	index;
	t_ul final_size;

	if ((size <= 0) || (new_size <= 0))
		return (NULL);
	if (pointer)
		string = (char *)pointer;
	final_size = new_size * type_size;
	size = size * type_size;
	result = malloc (final_size * sizeof(char));
	if (!result)
		return (free(pointer), end_program("Failed alloc re_alocker", 1), NULL);
	index = 0;
	while ((index < size) && (index < final_size) && (pointer != NULL))
	{
		result[index] = string[index];
		index++;
	}
	free(pointer);
	while (index < final_size)
		result[index++] = '\0';
	return (result);
}

int	string_appender(char **string, char *adition)
{
	int	size;
	int	string_size;

	if (!string || !adition || !(*adition))
		return (0);
	size = 0;
	string_size = string_length(*string);
	size += string_size;
	size += string_length(adition);
	size += 1;
	*string = re_allocker(*string, (string_size + 1), size, sizeof(**string));
	if (!string)
		return (end_program("Failed allocation in string_appender", 1), 0);
	if (!string_cat(*string, adition))
		end_program("Failed string_cat in string_appender", 1);
	return (1);
}

char	*string_duplicate(char *string)
{
	char *result;
	int	size;
	int	index;

	if (!string)
		return (NULL);
	size = string_length(string);
	if (size <= 0)
		return (NULL);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (end_program("Failed allocation in string_duplicate", 1), NULL);
	index = 0;	
	while (string[index])
	{
		result[index] = string[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}
