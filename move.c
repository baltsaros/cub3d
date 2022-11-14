/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:15:12 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/14 17:39:32 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    move_up(t_data *data)
{
    data->player_s.pos_win_y += data->player_s.speed * (data->player_s.delta_y / 2);
	data->player_s.pos_win_x += data->player_s.speed * (data->player_s.delta_x / 2);
	data->player_s.pos_y += data->player_s.speed * data->player_s.delta_y;
	data->player_s.pos_x += data->player_s.speed * data->player_s.delta_x;
}

void    move_down(t_data *data)
{
    data->player_s.pos_win_y -= data->player_s.speed * (data->player_s.delta_y / 2);
	data->player_s.pos_win_x -= data->player_s.speed * (data->player_s.delta_x / 2);
	data->player_s.pos_y -= data->player_s.speed * data->player_s.delta_y;
	data->player_s.pos_x -= data->player_s.speed * data->player_s.delta_x;
}

void    move_right(t_data *data)
{
    float   new_ang;
    float   delta_y_right;
    float   delta_x_right;
    
    new_ang = FixAng(data->player_s.p_ang + 90);
    delta_x_right = cos(degToRad(new_ang));
    delta_y_right = -sin(degToRad(new_ang));
    data->player_s.pos_win_y -= data->player_s.speed * (delta_y_right / 2);
    data->player_s.pos_win_x -= data->player_s.speed * (delta_x_right / 2);
    data->player_s.pos_y -= data->player_s.speed * delta_y_right;
    data->player_s.pos_x -= data->player_s.speed * delta_x_right;
}

void    move_left(t_data *data)
{
    float   new_ang;
    float   delta_y_right;
    float   delta_x_right;
    
    new_ang = FixAng(data->player_s.p_ang - 90);
    delta_x_right = cos(degToRad(new_ang));
    delta_y_right = -sin(degToRad(new_ang));
    data->player_s.pos_win_y -= data->player_s.speed * (delta_y_right / 2);
    data->player_s.pos_win_x -= data->player_s.speed * (delta_x_right / 2);
    data->player_s.pos_y -= data->player_s.speed * delta_y_right;
    data->player_s.pos_x -= data->player_s.speed * delta_x_right;
}