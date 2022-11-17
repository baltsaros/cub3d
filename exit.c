/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:19:11 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/17 17:55:52 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leave(t_data *data, int ret)
{
	mlx_destroy_image(data->mlx, data->background.img_ptr);
	mlx_destroy_image(data->mlx, data->walls.img_ptr);
	mlx_destroy_image(data->mlx, data->minimap.img_ptr);
	mlx_destroy_image(data->mlx, data->player.img_ptr);
	mlx_destroy_image(data->mlx, data->no_text.img.img_ptr);
	mlx_destroy_image(data->mlx, data->so_text.img.img_ptr);
	mlx_destroy_image(data->mlx, data->we_text.img.img_ptr);
	mlx_destroy_image(data->mlx, data->ea_text.img.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	data->mlx = NULL;
	data->win = NULL;
	cub_free_all(data);
	exit(ret);
}
