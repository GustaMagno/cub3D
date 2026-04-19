/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_basic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 22:23:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/14 23:08:38 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	string_length(char *string)
{
	int	size;

	if (!string)
		return (0);
	size = 0;
	while (string[size])
		size++;
	return (size);
}
