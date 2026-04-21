/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:52:17 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/21 01:24:32 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	main(int argc, char *argv[])
{
	t_all *all;

	all = NULL;
	init_structs(&all);
	fill_structs(all, argc, argv);
	parse(all);
	end_program(NULL, 0);
	return (0);
}
