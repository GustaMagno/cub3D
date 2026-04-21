/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:32:53 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/21 07:50:51 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	free_array_string(char **array_string, int size)
{
	int	line;

	if (!array_string)
		return (0);
	line = 0;
	while (((size > 0) && (line <= size)) || array_string[line])
	{
		free(array_string[line]);
		line++;
	}
	free(array_string);
	return (1);
}
