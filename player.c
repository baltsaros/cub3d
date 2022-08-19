/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/19 17:47:56 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_player(t_data *data)
{
    data->player.basic_color = 0x0FAE2;
    data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
		  &data->player.line_length, &data->player.endian);
    draw_square(data->player, data->player.basic_color, data->size_player, data->size_player);
    data->player_s.pos_win_x = data->minimap_s.position.x + data->player_s.pos_x;
    data->player_s.pos_win_y = data->minimap_s.position.y + data->player_s.pos_y;
    mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->player_s.pos_win_x, data->player_s.pos_win_y);
}

void    init_player_values(t_data *data)
{
    data->player_s.pos_x = 0;
    data->player_s.pos_y = 0;
    data->player_s.pos_win_x = 0;
    data->player_s.pos_win_y = 0;
    data->player_s.p_ang = 60;
    data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
    data->player.img_ptr = mlx_new_image(data->mlx, data->size_player, data->size_player);
    // Put check and error here
}