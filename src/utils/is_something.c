/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 04:54:16 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/21 04:01:31 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_white_space(char xar)
{
	if (!xar)
		return (0);
	if ((xar >= 9 && xar <= 13) || xar == 32)
		return (1);
	return (0);
}

int	is_alpha_numeric(char xar)
{
	if (!xar)
		return (0);
	if ((xar >= '0' && xar <= '9') || (xar >= 'a' && xar <= 'z')
		|| (xar >= 'A' && xar <= 'Z'))
		return (1);
	return (0);
}

