/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:18:43 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/22 14:01:20 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_data *data)
{
	t_ray_calcul	door;

	collisions_calculs_up_down(data, &door);
	if (data->map.map
		[door.ipy_add_yo][door.ipx_add_xo] == 'D')
		data->map.map[door.ipy_add_yo][door.ipx_add_xo] = 'C';
	else if (data->map.map
		[door.ipy_add_yo][door.ipx_add_xo] == 'C')
		data->map.map[door.ipy_add_yo][door.ipx_add_xo] = 'D';
}
