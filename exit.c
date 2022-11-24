/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:19:11 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/24 13:47:58 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_images(t_data *data)
{
	if (data->walls.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->walls.img_ptr);
	if (data->minimap.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->minimap.img_ptr);
	if (data->background.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->background.img_ptr);
	if (data->no_text.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->no_text.img.img_ptr);
	if (data->so_text.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->so_text.img.img_ptr);
	if (data->we_text.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->we_text.img.img_ptr);
	if (data->ea_text.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->ea_text.img.img_ptr);
	if (data->door_text.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->door_text.img.img_ptr);
}

int	ft_exit(t_data *data)
{
	free_images(data);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	data->mlx = NULL;
	data->win = NULL;
	cub_free_all(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	leave(t_data *data, int ret)
{
	free_images(data);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	data->mlx = NULL;
	data->win = NULL;
	cub_free_all(data);
	exit(ret);
}
