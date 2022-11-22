/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:18:43 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/22 23:30:04 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mono_raycast(t_data *data, t_ray_calcul ray)
{
	float	tan_c;
	int		posh;
	int		posv;
	int		pos;

	ray.is_door_h = 0;
	ray.is_door_v = 0;
	tan_c = tan(degtorad(ray.ra));
	posv = check_vertical_wall(data, &ray, tan_c);
	ray.vx = ray.rx;
	ray.vy = ray.ry;
	posh = check_horizontal_wall(data, &ray, (1.0 / tan_c));
	pos = adapt_distance(&ray, posh, posv);

	printf("ray.mx: %f\n", ray.mx);
	printf("ray.my: %f\n", ray.my);
}

void	open_door(t_data *data)
{
	t_ray_calcul	door;

	mono_raycast(data, data->ray_calcul);

	collisions_calculs_up_down(data, &door);
	if (data->map.map
		[door.ipy_add_yo][door.ipx_add_xo] == 'D')
		data->map.map[door.ipy_add_yo][door.ipx_add_xo] = 'C';
	else if (data->map.map
		[door.ipy_add_yo][door.ipx_add_xo] == 'C')
		data->map.map[door.ipy_add_yo][door.ipx_add_xo] = 'D';
}
