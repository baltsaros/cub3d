/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:18:43 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/18 22:49:43 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    open_door(t_data *data)
{
    t_ray_calcul    door;

    collisions_calculs_up_down(data, &door);
    if (data->map.map
        [door.ipy_add_yo][door.ipx_add_xo] == 'D')
        data->map.map[door.ipy_add_yo][door.ipx_add_xo] = '0';
}