#include "utils.h"

int	is_white_space(char xar)
{
	if (!xar)
		return (0);
	if ((xar >= 9 && xar <= 13) || xar == 32)
		return (1);
	return (0);
}
