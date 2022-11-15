/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:57:43 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/15 14:19:47 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    collisions_calculs(t_data *data, t_ray_calcul *collisions)
{
    int xo;
    int yo;

    xo = 0;
    yo = 0;
    if (data->player_s.delta_x < 0)
        xo = -data->player_s.speed;
    else
        xo = data->player_s.speed;
    if (data->player_s.delta_y < 0)
        yo = -data->player_s.speed;
    else
        yo = data->player_s.speed;
    collisions->ipx = data->player_s.pos_x / SQUARE_SIZE;
    collisions->ipx_add_xo = (data->player_s.pos_x + xo) / SQUARE_SIZE;
    collisions->ipx_sub_xo = (data->player_s.pos_x - xo) / SQUARE_SIZE;
    collisions->ipy = data->player_s.pos_y / SQUARE_SIZE;
    collisions->ipy_add_yo = (data->player_s.pos_y + yo) / SQUARE_SIZE;
    collisions->ipy_sub_yo = (data->player_s.pos_y - yo) / SQUARE_SIZE;

    // printf("aaaah delta_x: %f\n", data->player_s.delta_x);
    // printf("aaaah delta_y: %f\n", data->player_s.delta_y);

    // printf("aaaah ipy: %d\n", collisions->ipy);
    // printf("aaah ipx_add_xo: %d\n", collisions->ipx_add_xo);
    // printf("aaah ipx_add_yo: %d\n", collisions->ipy_add_yo);
    // printf("aaaah ipx: %d\n", collisions->ipx);
}