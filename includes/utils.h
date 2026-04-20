/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 22:23:52 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/20 05:58:48 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef UTILS_H
# define UTILS_H

# include "cub3D.h"

//=====- allocation.c -=========================================================
void	*re_allocker(void *ptr, t_ul size, t_ul new_size, t_ul type_sz); // Returns a new memory of new_size's size, with the content of *ptr inside
char	*string_duplicate(char *string); // Returns an allocated copy of the string
int		string_appender(char **string, char *adition); // Reallocs 'string' memory to add 'adition' in front of it

//=====- allocation_free.c -====================================================
int		free_array_string(char **array_string, int size); // Size is optional, send 0 for std

//=====- string_advanced.c -====================================================
int		string_cat(char *string1, char *string2); // Concatenates a string2 in string1
int		string_compare(char *string1, char *string2, int until); //'Until' is optional, send 0 for std.
int		memory_zero(void *memory, t_ul size, t_ul type_size); // Sets every byte to zero
int		array_string_length(char **array); //Returns the number of strings in the array of strings
int     string_trim(char *string); //Cuts whitespaces at the beginning and end of the string

//=====- string_basic.c -=======================================================
int		string_length(char *string); // Returns the number of 'char's in the string

//=====- get_next_line_no_breakline.c -======================================================
char	*get_next_line_no_breakline(int fd); // Returns next line of file pointed by 'fd', excluding the ending '\n' of string
char	*liner(char *line, t_gnl *x, int *all_end, char *buffer); //Helper of get_next_line_no_breakline

//=====- print.c -==============================================================
int		print_message(char *message, int fd, int break_line); //Writes the string in the specific file descriptor. Send "break_line" to 'true' to end with '\n'
int     print_errors(char **messages); //Writes multiple strings in the STDERR, then '\n'
int		print_error(char *message);//Writes the string in stderr, and writes '\n'
int     print_map(char **map); // Print an array[string]'s "map";

//=====- clean_data.c -=========================================================
void	end_program(char *error_message, int status);//Error is optional ~ NULL for std
int		clear_config(t_config *config); //Free's all config strings
int     clean_maps(t_map *maps);

//=====- is_something.c -=======================================================
int		is_white_space(char xar); //Check if the given character is an white_space

#endif