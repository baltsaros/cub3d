/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/13 19:13:48 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_player(t_data *data)
{
    data->player.basic_color = 0x000000;
    draw_square(data->player, data->player.basic_color, PLAYER_SIZE / 2, PLAYER_SIZE / 2);
    data->player_s.pos_win_x = data->minimap_s.position.x + (data->player_s.pos_x / 2);
	data->player_s.pos_win_y = data->minimap_s.position.y + (data->player_s.pos_y / 2);
    mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->player_s.pos_win_x, data->player_s.pos_win_y);
}

void    init_player_pos(t_data *data, int height, int width)
{
    int i;
    int j;

    i = 0;
    while (i != height)
    {
        j = 0;
        while (j != width)
        {
            if (data->map.map[i][j] == 'N')
            {
                data->player_s.pos_x = (j * SQUARE_SIZE) + (SQUARE_SIZE / 2) - (PLAYER_SIZE / 2);
                data->player_s.pos_y = (i * SQUARE_SIZE) + (SQUARE_SIZE / 2) - (PLAYER_SIZE / 2);
            }
            j++;
        }
        i++;
    }
}

int init_player_values(t_data *data)
{
	data->player_s.pos_x = 0;
	data->player_s.pos_y = 0;
	data->player_s.p_ang = 90;
	data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
    init_player_pos(data, data->map.height, data->map.width);
    data->player_s.speed = 10;
    return (0);
}