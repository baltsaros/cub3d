/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/17 18:44:21 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_check_exit(int input, char *str, t_data *data)
{
	size_t	len;

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

int	error_check_noexit(int input, char *str)
{
	size_t	len;

	if (input < 0)
	{
		write(2, "Cub3d: ", 7);
		len = ft_strlen(str);
		write(2, str, len);
		perror("");
	}
	return (input);
}

void	error_exit(t_data *data, char *msg, int param)
{
	size_t	len;

	len = ft_strlen(msg);
	write(2, "Cub3d: ", 7);
	write(2, msg, len);
	write(2, "\n", 1);
	if (param)
		cub_free_all(data);
	exit(EXIT_FAILURE);
}

void	check_mlx(void *mlx, t_data *data)
{
	if (!mlx)
	{
		write(2, "Cub3d: ", 7);
		write(2, "Mlx init error\n", 15);
		leave(data, EXIT_FAILURE);
	}
}

void	check_win(t_data *data)
{
	if (!data->win)
	{
		write(2, "Cub3d: ", 7);
		write(2, "Windows is broken!\n", 19);
		leave(data, EXIT_FAILURE);
	}
}
