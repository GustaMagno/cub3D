/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 18:21:29 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/19 08:19:43 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_structs(t_all **all)
{
	(*all) = malloc(sizeof(t_all));
	if (!(*all))
		end_program("Failed malloc of \"all\" struct", 1);
	*(*all) = (t_all){0};
	(*all)->maps = malloc(sizeof(t_map));
	if (!(*all)->maps)
		end_program("Failed malloc of \"all->maps\" struct", 1);
	*((*all)->maps) = (t_map){0};
	(*all)->conf = malloc(sizeof(t_config));
	if (!(*all)->conf)
		end_program("Failed malloc of \"all->conf\"", 1);
	*((*all)->conf) = (t_config){0};
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
	return (1);
}

int	fill_structs(t_all *all, int argc, char **argv)
{
	if (!all)
		return (0);
	get_all_reference(all);
	all->argc = argc;
	all->argv = argv;
	if (argc > 1)
		all->maps->name = string_duplicate(argv[1]);
	fill_config(all->conf);
	return (1);
}

int	clear_config(t_config *config)
{
	if (!config)
		return (0);
	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
	if (config->f)
		free(config->f);
	if (config->c)
		free(config->c);
	free(config);
	return (1);
}

void	end_program(char *error, int status)
{
	static t_all *all;

	if (all == NULL)
	{
		all = get_all_reference(NULL);
		return ;
	}
	if (all->maps)
	{
		if (all->maps->name)
			free(all->maps->name);
		if (all->maps->adress)
			free(all->maps->adress);
		if (all->maps->file)
			free_array_string(all->maps->file, 0);
		free(all->maps);
	}
	if (all->conf)
		clear_config(all->conf);
	if (all)
		free(all);
	if (error != NULL)
		put_error(error);
	exit(status);
}
