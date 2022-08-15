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
		cub_free_all(data);
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

void	error_exit(t_input *data, char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(2, "Cub3d: ", 7);
	write(2, msg, len);
	write(2, "\n", 1);
	cub_free_all(data);
	exit(EXIT_FAILURE);
}

void	check_mlx(void *mlx)
{
	if (!mlx)
	{
		write(2, "Cub3d: ", 7);
		write(2, "Mlx init error\n", 15);
		exit(EXIT_FAILURE);
	}
}

void	check_win(t_input *data)
{
	if (!data->win)
	{
		write(2, "Cub3d: ", 7);
		write(2, "Windoes is broken!\n", 19);
		// mlx_destroy_image(data->mlx, data->img.mlx_img);
		exit(EXIT_FAILURE);
	}
}
