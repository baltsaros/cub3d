/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/14 14:16:50 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_player(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (0);
    return (1);
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
            if (!is_player(data->map.map[i][j]))
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
	data->player_s.p_ang = data->map.angle;
	data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
    init_player_pos(data, data->map.height, data->map.width);
    data->player_s.speed = 10;
    data->player_s.pos_win_x = data->minimap_s.position.x + (data->player_s.pos_x / 2);
	data->player_s.pos_win_y = data->minimap_s.position.y + (data->player_s.pos_y / 2);
    return (0);
}