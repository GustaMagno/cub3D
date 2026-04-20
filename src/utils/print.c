/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:20:12 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/20 05:43:00 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

int	print_message(char *message, int fd, int break_line)
{
	int	size;

	if (!message || fd < 0)
		return (0);
	size = string_length(message);
	if (size <= 0)
		return (0);
	write(fd, message, size);
	if (break_line == true)
		write(1, "\n", 1);
	return (1);
}

int	print_error(char *message)
{
	static char	*standard_error;
	static int	error_size;
	int size;

	if (!standard_error || !error_size)
	{
		standard_error = SUBJECT_ERROR;
		error_size = string_length(standard_error);
	}
	if (!message)
		return (0);
	size = string_length(message);
	if (size <= 0)
		return (0);
	write(STDERR_FILENO, standard_error, error_size);
	write(STDERR_FILENO, message, size);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	print_errors(char **messages)
{
	static char *standard_error;
	static int	error_size;
	int	size;
	int	line;

	if (!standard_error || !!error_size)
	{
		standard_error = SUBJECT_ERROR;
		error_size = string_length(standard_error);
	}
	if (!messages)
		return (0);
	write(STDERR_FILENO, standard_error, error_size);
	line = 0;
	while (messages[line])
	{
		print_message(messages[line], STDERR_FILENO, false);
		line++;
	}
	write(1, "\n", 1);
	return (1);
}

int	print_map(char **map)
{
	int	line;

	if (!map)
		return (0);
	line = 0;
	while (map[line])
	{
		print_message(map[line], STDOUT_FILENO, true);
		line++;
	}
	return (0);
}
