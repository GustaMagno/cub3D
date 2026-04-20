/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 23:03:46 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/20 03:52:47 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

int	string_compare(char *string1, char *string2, int until)
{
	int	index;

	if (!string1 || !string2)
		return (0);
	index = 0;
	while (string1[index] && string2[index]
		&& (string1[index] == string2[index]))
	{
		if ((until > 0) && !(index < (until - 1)))
			break ;
		index++;
	}
	return (string1[index] - string2[index]);
}

int	string_cat(char *string1, char *string2)
{
	int	index2;
	int	index;

	if (!string1 || !string2)
		return (0);
	index = 0;
	while (string1[index])
		index++;
	index2 = 0;
	while (string2[index2])
	{
		string1[index] = string2[index2];
		index++;
		index2++;
	}
	string1[index] = '\0';
	return (1);
}

int	memory_zero(void *memory, t_ul size, t_ul type_size)
{
	char *string;
	int	index;
	int	limit;

	if (!memory)
		return (0);
	limit = size * type_size;
	string = (char *)memory;
	index = 0;
	while (index < limit)
	{
		string[index] = 0;
		index++;
	}
	return (1);
}

int	array_string_length(char **array)
{
	int	size;

	if (!array)
		return (0);
	size = 0;
	while (array[size])
		size++;
	return (size);
}

int	string_trim(char *string)
{
	int	start;
	int	end;
	int	index;

	if (!string)
		return (0);
	end = string_length(string);
	while (is_white_space(string[--end]))
		string[end] = '\0';
	start = 0;
	while (is_white_space(string[start]) == true)
		start++;
	index = 0;
	while (string[start])
		string[index++] = string[start++];
	while (end > index)
		string[end--] = '\0';
	return (1);
}

// int	main(void)
// {
// 	printf("result: %d\n", string_compare("Tudo bem", "Tudo bem"));
// }