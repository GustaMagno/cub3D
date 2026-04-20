#include "utils.h"

int	free_array_string(char **array_string, int size)
{
	int	line;

	if (!array_string)
		return (0);
	line = 0;
	while (((size > 0) && (line <= size)) || array_string[line])
	{
		free(array_string[line]);
		line++;
	}
	if (size == 0)
		free(array_string[line]);
	free(array_string);
	return (1);
}
