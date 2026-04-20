/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:43:25 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/20 01:50:50 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

int	clean_config(t_config *config)
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

int	clean_maps(t_map *maps)
{
	if (!maps)
		return (0);
	if (maps->name)
		free(maps->name);
	if (maps->adress)
		free(maps->adress);
	if (maps->map)
		free(maps->map);
	if (maps->file)
		free_array_string(maps->file, 0);
	free(maps);
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
		clean_maps(all->maps);
	if (all->conf)
		clean_config(all->conf);
	if (all)
		free(all);
	if (error != NULL)
		print_error(error);
	exit(status);
}
