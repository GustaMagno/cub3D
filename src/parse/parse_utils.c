/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 04:55:03 by olacerda          #+#    #+#             */
/*   Updated: 2026/05/26 23:34:49 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	adress_is_valid(char *adress)
{
	int fd;

	if (!adress)
		return (0);
	fd = open(adress, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	is_valid(char xar, int w_spaces)
{
	char *valid;
	int	index;

	if (!xar)
		return (0);
	if (w_spaces == false)
		valid = VALID_CHARACTERS;
	else
		valid = VALID_CHARACTERS_W_SPACE;
	index = 0;
	while (valid[index])
	{
		if (xar == valid[index])
			return (1);
		index++;
	}
	return (0);
}

int	is_config(char *string, t_config *conf)
{
	int	line;

	if (!string || !conf)
		return (0);
	line = 0;
	while (conf->ref[line])
	{
		if (string_compare(string, conf->ref[line], string_length(conf->ref[line])) == 0)
		{
			set_config_content(string, conf->ref[line], conf);
			return (1);
		}
		line++;
	}
	return (0);
}

int	check_lines(char **map)
{
	int	line;
	int	column;

	if (!map)
		return (0);
	line = 0;
	while (map[line])
	{
		column = 0;
		while (map[line][column])
		{
			if (is_valid(map[line][column], false))
			{
				if (map[line][column] != '1')
					return (0);
				while (map[(line)] && is_valid(map[line][column], false))
					column++;
				if ((--column >= 0) && map[line][column] != '1')
					return (0);
			}
			column++;
		}
		line++;
	}
	return (1);
}

int	check_columns(char **map, int column_size)
{
	int	line;
	int	column;

	if (!map || !(*map))
		return (0);
	column = 0;
	line = 0;
	(void)column_size;
	while (map[line] && map[line][column])
	{
		printf("1\n");
		while (map[line] && map[line][column])
		{
			printf("2\n");
			if (is_valid(map[line][column], false))
			{
				printf("3\n");
				if (map[line][column] != '1')
					return (0);
				printf("4\n");
				while (map[(line)] && is_valid(map[line][column], false))
					line++;
				printf("5\n");
				if ((--line >= 0) && map[line] && map[line][column] != '1')
					return (0);
				printf("6\n");
			}
			line++;
		}
		printf("7\n");
		column++;
		line = 0;
	}
	return (1);
}

int	set_player_info(t_play *player, int line, int column, char **map)
{
	if (!player || !map)
		return (0);
	player->line = line;
	player->column = column;
	if (map[line][column] == 'N')
		player->direction = NO;
	if (map[line][column] == 'S')
		player->direction = SO;
	if (map[line][column] == 'E')
		player->direction = EA;
	if (map[line][column] == 'W')
		player->direction = WE;
	return (1);
}
