#include "cub3d.h"

void	cub_free(char *str[])
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
	free(str);
}