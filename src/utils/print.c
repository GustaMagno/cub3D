/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:20:12 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/21 07:17:14 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	print_errors(char **messages, int line, int column, int coordinates)
{
	static char *standard_error;
	static int	error_size;
	int	index;

	if (!standard_error || !!error_size)
	{
		standard_error = SUBJECT_ERROR;
		error_size = string_length(standard_error);
	}
	if (!messages)
		return (0);
	write(STDERR_FILENO, standard_error, error_size);
	index = -1;
	while (messages[++index])
		print_message(messages[index], STDERR_FILENO, false);
	if (coordinates == true)
	{
		print_message("Line:", STDERR_FILENO, false);
		print_number(line);
		print_message(" Column:", STDERR_FILENO, false);
		print_number(column);
	}
	write(1, "\n", 1);
	return (1);
}

int	map_debugger(char **map, char *message)
{
	int	line;
	
	if (!map || !message)
		return (0);
	line = 0;	
	printf("%s\n", message);
	while (map[line])
	{
		printf("maps[%d]: %s\n",line, map[line]);
		line++;
	}
	if (map[line] == NULL)
		printf("maps[%d] is NULL\n", line);
	return (1);
}

void	print_number(int number)
{
	long	nbr;

	nbr = number;
	if (nbr < 0)
	{
		write(STDOUT_FILENO, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
		print_number(nbr / 10);
	write(STDOUT_FILENO, &(char){(nbr % 10) + 48}, 1);
}