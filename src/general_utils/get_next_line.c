/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_no_breakline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 23:56:29 by otlacerd          #+#    #+#             */
/*   Updated: 2026/04/18 03:36:03 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

char	*liner(char *line, t_gnl *x, int *all_end, char *buffer)
{
	char	*new_line;
	int		index;

	if (!x || !all_end)
		return (NULL);
	while ((buffer[x->end] != '\n') && (x->end < x->readbytes))
	{
		x->end++;
		(*all_end)++;
	}
	new_line = malloc((*all_end + 1) * sizeof(char));
	if (!new_line)
		return (free(line), end_program("Failed allocation in liner", 1), NULL);
	index = -1;
	while (++index < (*all_end - x->end) && line)
		new_line[index] = line[index];
	while ((x->start < x->end) && (x->start < x->readbytes))
		new_line[index++] = buffer[(x->start)++];
	new_line[index] = '\0';
	free(line);
	x->start += (buffer[x->start] == '\n');
	return (new_line);
}

char *get_next_line_no_breakline(int fd)
{
	static t_gnl	x[FD_SETSIZE];
	char			(buff[BUFFER_SIZE + 1])[FD_SETSIZE];
	char 			*line;
	int				all_end;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (x[fd].start >= x[fd].readbytes)
		x[fd] = (t_gnl){BUFFER_SIZE, 0, BUFFER_SIZE};
	line = NULL;
	all_end = 0;
	while (((buff[fd])[x[fd].end] != 10 || line == NULL) && x[fd].readbytes > 0)
	{
		if (x[fd].start >= x[fd].readbytes)
		{
			x[fd].readbytes = read(fd, (buff[fd]), BUFFER_SIZE);
			if (x[fd].readbytes == -1)
				return (free(line), NULL);
			if (x[fd].readbytes == 0)
				break ;
			*((long *)(&(x[fd].start))) = 0;
		}
		line = liner(line, &(x[fd]), &all_end, buff[fd]);
	}
	return (x[fd].end += ((buff[fd])[x[fd].end] == '\n'), line);
}

// int	main(void)
// {
// 	char *line;
// 	int	fd[3];

	
// 	fd[0] = open("teste.txt", O_RDONLY);
// 	fd[1] = open("teste1.txt", O_RDONLY);
// 	fd[2] = open("teste2.txt", O_RDONLY);
// 	if (fd[0] < 0 || fd[1] < 0  || fd[2] < 0 )
// 		return (printf("falhou\n"), 1);
// 	line = " ";
// 	int	count = 3;
// 	int	index2 = 0;
// 	int index;
// 	while (line)
// 	{
// 		printf("line: %d\n", index2);
// 		index = 0;
// 		while (index < count)
// 		{
// 			line = get_next_line_no_breakline(fd[index]);
// 			if (!line && index2 == 4)
// 				break;
// 			printf("%s", line);
// 			if (index2 == 4)
// 				printf("\n");
// 			free(line);
// 			index++;
// 		}
// 		index2++;
// 		printf("\n\n");
// 	}
// 	index = 0;
// 	while (index < count)
// 		close(fd[index++]);
// 	return (1);
// }
