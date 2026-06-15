/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:40:37 by otlacerd          #+#    #+#             */
/*   Updated: 2026/06/15 17:40:39 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3D.h"

void	*re_allocker(void *ptr, t_ul size, t_ul new_size, t_ul type_sz);
char	*string_duplicate(char *string);
int		string_appender(char **string, char *adition);

int		free_array_string(char **array_string, int size);

int		string_cat(char *string1, char *string2);
int		string_compare(char *string1, char *string2, int until);
int		memory_zero(void *memory, t_ul size, t_ul type_size);
int		array_string_length(char **array);
int		string_trim(char *string);

int		string_length(char *string);

char	*get_next_line_no_breakline(int fd);
char	*liner(char *line, t_gnl *x, int *all_end, char *buffer);

int		print_message(char *message, int fd, int break_line);
int		print_errors(char **messages, int line, int column, int coordinates);
int		print_error(char *message);
void	print_number(int number);

void	end_program(char *error_message, int status);
int		clear_config(t_config *config);
int		clean_maps(t_map *maps);

int		is_numeric(char xar);
int		is_white_space(char xar);
int		is_alpha_numeric(char xar);

#endif