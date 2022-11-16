/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:15:12 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/16 14:44:43 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    move_up(t_data *data, t_ray_calcul *collisions)
{
    if (data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == '0' 
        || !is_player(data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
    {
        data->player_s.pos_win_x += data->player_s.speed * (data->player_s.delta_x / 2);
        data->player_s.pos_x += data->player_s.speed * data->player_s.delta_x;
    }
    if (data->map.map[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == '0'
        || !is_player(data->map.map[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
    {
        data->player_s.pos_win_y += data->player_s.speed * (data->player_s.delta_y / 2);
	    data->player_s.pos_y += data->player_s.speed * data->player_s.delta_y;
    }
}

void    move_down(t_data *data, t_ray_calcul *collisions)
{
    if (data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_sub_xo] == '0' 
        || !is_player(data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_sub_xo]))
    {
        data->player_s.pos_win_x -= data->player_s.speed * (data->player_s.delta_x / 2);
        data->player_s.pos_x -= data->player_s.speed * data->player_s.delta_x;
    }
    if (data->map.map[collisions->ipy_sub_yo][collisions->ipx / SQUARE_SIZE] == '0'
        || !is_player(data->map.map[collisions->ipy_sub_yo][collisions->ipx / SQUARE_SIZE]))
    {
        data->player_s.pos_win_y -= data->player_s.speed * (data->player_s.delta_y / 2);
	    data->player_s.pos_y -= data->player_s.speed * data->player_s.delta_y;
    }
}

void    move_right(t_data *data, t_ray_calcul *collisions)
{
    if (data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == '0' 
        || !is_player(data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
    {
        data->player_s.pos_win_x -= data->player_s.speed * (data->player_s.delta_y / 2);
        data->player_s.pos_x -= data->player_s.speed * data->player_s.delta_y;
    }
    if (data->map.map[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == '0'
        || !is_player(data->map.map[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
    {
        data->player_s.pos_win_y -= data->player_s.speed * (-data->player_s.delta_x / 2);
        data->player_s.pos_y -= data->player_s.speed * -data->player_s.delta_x;
    }
}

void    move_left(t_data *data, t_ray_calcul *collisions)
{
    if (data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == '0' 
        || !is_player(data->map.map[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
    {
        data->player_s.pos_win_x -= data->player_s.speed * (-data->player_s.delta_y / 2);
        data->player_s.pos_x -= data->player_s.speed * -data->player_s.delta_y;
    }
    if (data->map.map[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == '0'
        || !is_player(data->map.map[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
    {
        data->player_s.pos_win_y -= data->player_s.speed * (data->player_s.delta_x / 2);
        data->player_s.pos_y -= data->player_s.speed * data->player_s.delta_x;
    }
}

void    move(t_data *data)
{
    t_ray_calcul    collisions;
    
    if (data->keyboard.w || data->keyboard.s)
    {
        collisions_calculs_up_down(data, &collisions);
        if (data->keyboard.w && !data->keyboard.d && !data->keyboard.a)
            move_up(data, &collisions);
        if (data->keyboard.s && !data->keyboard.d && !data->keyboard.a)
            move_down(data, &collisions);
    }
    if (data->keyboard.d || data->keyboard.a)
    {
        collisions_calculs_right(data, &collisions);
        if (data->keyboard.d && !data->keyboard.w && !data->keyboard.s)
            move_right(data, &collisions);
        collisions_calculs_left(data, &collisions);
        if (data->keyboard.a && !data->keyboard.w && !data->keyboard.s)
            move_left(data, &collisions);
    }
}