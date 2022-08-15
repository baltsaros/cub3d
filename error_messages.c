#include "cub3d.h"

int	error_check_exit(int input, char *str, t_input *data)
{
	size_t	len;

	(void)data;
	if (input < 0)
	{
		write(2, "Cub3d: ", 7);
		len = ft_strlen(str);
		write(2, str, len);
		perror("");
		exit (1);
	}
	return (input);
}

int	error_check_noexit(int input, char *str, t_input *data)
{
	size_t	len;

	(void)data;
	if (input < 0)
	{
		write(2, "Cub3d: ", 7);
		len = ft_strlen(str);
		write(2, str, len);
		perror("");
	}
	return (input);
}
