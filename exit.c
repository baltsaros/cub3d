/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:19:11 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 16:16:28 by mthiry           ###   ########.fr       */
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
	if (data->sprite_1.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->sprite_1.img.img_ptr);
	if (data->sprite_2.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->sprite_2.img.img_ptr);
	if (data->sprite_3.img.img_ptr != NULL)
		mlx_destroy_image(data->mlx, data->sprite_3.img.img_ptr);
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
