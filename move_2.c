/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:07:56 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/24 16:25:40 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    move_up_right(t_data *data)
{
    float   move_x;
    float   move_y;

    // move_x = sqrt(pow(data->player_s.speed * data->player_s.delta_x, 2)
    //     + pow(data->player_s.speed * data->player_s.delta_y, 2));
    // move_y = sqrt(pow(data->player_s.speed * data->player_s.delta_y, 2)
    //     + pow(data->player_s.speed * -data->player_s.delta_x, 2));

    move_x = (data->player_s.speed * data->player_s.delta_x) - (data->player_s.speed * data->player_s.delta_y);
    move_y = (data->player_s.speed * data->player_s.delta_y) - (data->player_s.speed * -data->player_s.delta_x);

    data->player_s.pos_x += move_x;
    data->player_s.pos_y += move_y;
}

// void    move_up_left(t_data *data)
// {

// }

// void    move_down_right(t_data *data)
// {

// }

// void    move_down_left(t_data *data)
// {

// }

void    diagonal_move(t_data *data)
{
    if (data->keyboard.w && data->keyboard.d)
        move_up_right(data);
}