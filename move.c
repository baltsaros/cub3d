/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:15:12 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/15 18:03:04 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    move_up(t_data *data, t_ray_calcul *collisions)
{
    (void)collisions;
    // t_point col_x;
    // t_point col_y;

    // col_x.y = (collisions->ipy * data->map.width + collisions->ipx_add_xo) / data->map.height;
    // col_x.x = collisions->ipy * data->map.width + collisions->ipx_add_xo;
    // printf("col_x.y: %d\n", col_x.y);
    // printf("col_y.x: %d\n", col_x.x);

    // if (data->map.map[col_x.y][col_x.x] == '0')
    // {
        data->player_s.pos_win_x += data->player_s.speed * (data->player_s.delta_x / 2);
        data->player_s.pos_x += data->player_s.speed * data->player_s.delta_x;
    // }
    // col_y.y = (collisions->ipy_add_yo * data->map.width + collisions->ipx) / data->map.height;
    // col_y.x = 0;
    // if (data->map.map[col_y.y][col_y.x] == '0')
    // {
        data->player_s.pos_win_y += data->player_s.speed * (data->player_s.delta_y / 2);
	    data->player_s.pos_y += data->player_s.speed * data->player_s.delta_y;
    // }
}

void    move_down(t_data *data, t_ray_calcul *collisions)
{
    (void)collisions;
    // if (data->map.map[collisions->ipy * data->map.width + collisions->ipx_sub_xo] == 0)
    // {
        data->player_s.pos_win_x -= data->player_s.speed * (data->player_s.delta_x / 2);
        data->player_s.pos_x -= data->player_s.speed * data->player_s.delta_x;
    // }
    // if (data->map.map[collisions->ipy_sub_yo * data->map.width + collisions->ipx] == 0)
    // {
        data->player_s.pos_win_y -= data->player_s.speed * (data->player_s.delta_y / 2);
	    data->player_s.pos_y -= data->player_s.speed * data->player_s.delta_y;
    // }
}

void    move_right(t_data *data, t_ray_calcul *collisions)
{
    (void)collisions;

    data->player_s.pos_win_x -= data->player_s.speed * (data->player_s.delta_y / 2);
    data->player_s.pos_x -= data->player_s.speed * data->player_s.delta_y;

    data->player_s.pos_win_y -= data->player_s.speed * (-data->player_s.delta_x / 2);
    data->player_s.pos_y -= data->player_s.speed * -data->player_s.delta_x;
}

void    move_left(t_data *data, t_ray_calcul *collisions)
{
    (void)collisions;
    
    data->player_s.pos_win_x -= data->player_s.speed * (-data->player_s.delta_y / 2);
    data->player_s.pos_x -= data->player_s.speed * -data->player_s.delta_y;

    data->player_s.pos_win_y -= data->player_s.speed * (data->player_s.delta_x / 2);
    data->player_s.pos_y -= data->player_s.speed * data->player_s.delta_x;
}

void    move_mult_up(t_data *data, t_ray_calcul *collisions)
{
    (void)collisions;
    if (data->keyboard.d)
    {
        data->player_s.pos_win_x += data->player_s.speed * (data->player_s.delta_x / 2);
        data->player_s.pos_x += data->player_s.speed * data->player_s.delta_x;
    }
    else if (data->keyboard.a)
    {
        data->player_s.pos_win_y += data->player_s.speed * (data->player_s.delta_y / 2);
	    data->player_s.pos_y += data->player_s.speed * data->player_s.delta_y;
    }
}

void    move_mult_down(t_data *data, t_ray_calcul *collisions)
{
    (void)collisions;
    if (data->keyboard.d)
    {
        data->player_s.pos_win_x -= data->player_s.speed * (data->player_s.delta_x / 2);
        data->player_s.pos_x -= data->player_s.speed * data->player_s.delta_x;
    }
    else if (data->keyboard.a)
    {
        data->player_s.pos_win_y -= data->player_s.speed * (data->player_s.delta_y / 2);
	    data->player_s.pos_y -= data->player_s.speed * data->player_s.delta_y;
    }
}

void    move(t_data *data)
{
    t_ray_calcul    collisions;
    
    collisions_calculs(data, &collisions);
    if (data->keyboard.w && (data->keyboard.d || data->keyboard.a))
        move_mult_up(data, &collisions);
    else if (data->keyboard.s && (data->keyboard.d || data->keyboard.a))
        move_mult_down(data, &collisions);
    else
    {
        if (data->keyboard.w)
            move_up(data, &collisions);
        if (data->keyboard.a)
            move_left(data, &collisions);
        if (data->keyboard.s)
            move_down(data, &collisions);
        if (data->keyboard.d)
            move_right(data, &collisions);
    }
}