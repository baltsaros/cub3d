/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 19:01:28 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/14 13:40:27 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_img(t_data *data)
{
    data->background.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->walls.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->minimap.img_ptr = mlx_new_image(data->mlx, data->minimap_s.width, data->minimap_s.height);
    data->player.img_ptr = mlx_new_image(data->mlx, PLAYER_SIZE / 2, PLAYER_SIZE / 2);
    if (!data->background.img_ptr || !data->walls.img_ptr || !data->minimap.img_ptr || !data->player.img_ptr)
        return (1);
    data->background.addr = mlx_get_data_addr(data->background.img_ptr, &data->background.bpp,
		        &data->background.line_length, &data->background.endian);
    data->walls.addr = mlx_get_data_addr(data->walls.img_ptr, &data->walls.bpp,
                &data->walls.line_length, &data->walls.endian);
    data->minimap.basic_color = 0x88000000;
    data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr, &data->minimap.bpp,
                &data->minimap.line_length, &data->minimap.endian);
    data->player.basic_color = 0x000000;
    data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
		        &data->player.line_length, &data->player.endian);
    return (0);
}