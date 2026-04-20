/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:59:59 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/20 21:41:20 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_all	*init_structs()
{
	t_all *all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (NULL);
	return (all);
}

t_all	*get_all_reference(t_all *all)
{
	static t_all *reference;

	if (all != NULL)	
		reference = all;
	else if (all == NULL)
		return (reference);
}

void	end_structs(char *message, int status)
{
	static t_all *all;

	if (all == NULL)
		all = get_all_reference(NULL);
	if (all)
		free(all);

	exit(status);
}

