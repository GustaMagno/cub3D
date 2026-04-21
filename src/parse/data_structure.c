/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:21:29 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/21 06:41:57 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	init_structs(t_all **all)
{
	(*all) = malloc(sizeof(t_all));
	if (!(*all))
	{
		print_error("Failed malloc of \"all\" in init structs");
		exit(1);
	}
	get_all_reference(*all);
	*(*all) = (t_all){0};
	(*all)->maps = malloc(sizeof(t_map));
	if (!(*all)->maps)
		end_program("Failed malloc of \"all->maps\" struct", 1);
	*((*all)->maps) = (t_map){0};
	(*all)->conf = malloc(sizeof(t_config));
	if (!(*all)->conf)
		end_program("Failed malloc of \"all->conf\"", 1);
	*((*all)->conf) = (t_config){0};
	(*all)->play = malloc(sizeof(t_play));
	if (!(*all)->play)
		end_program("Failed malloc of \"all->play\"", 1);
	*((*all)->play) = (t_play){0};
}

t_all	*get_all_reference(t_all *all)
{
	static t_all *reference;

	if (all != NULL)	
	{
		reference = all;
		end_program(NULL, 0);
		return (NULL);
	}
	return (reference);
}

int	fill_config(t_config *conf)
{
	if (!conf)
		return (0);
	conf->ref[NO] = DIR_NORTH;
	conf->ref[SO] = DIR_SOUTH;
	conf->ref[WE] = DIR_WEST;
	conf->ref[EA] = DIR_EAST;
	conf->ref[F] = TEX_FLOOR;
	conf->ref[C] = TEX_CEIL;
	conf->ref[END] = NULL;
	conf->count = array_string_length(conf->ref);
	return (1);
}

int	fill_structs(t_all *all, int argc, char **argv)
{
	if (!all)
		return (0);
	all->argc = argc;
	all->argv = argv;
	if (argc > 1)
		all->maps->name = string_duplicate(argv[1]);
	fill_config(all->conf);
	// all->maps->valid_chars = VALID_CHARACTERS;
	return (1);
}
