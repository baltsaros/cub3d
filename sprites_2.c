/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:31:38 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 17:50:14 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_horizontal_sprite(t_data *data, t_ray_calcul *ray, int index)
{
	while ((size_t)index < data->map.height)
	{
		ray->mx = ((int)(ray->rx) / SQUARE_SIZE);
		ray->my = ((int)(ray->ry) / SQUARE_SIZE);
		if (is_within_maps(ray->my, ray->mx, data->map.height, data->map.width)
			&& (is_wall(data->map.map[ray->my][ray->mx])
            || data->map.map[ray->my][ray->mx] == 'P'))
		{
            if (data->map.map[ray->my][ray->mx] == 'P')
				ray->is_sprite_h = 1;
            // ray->ry += ray->yo / 2;
			index = data->map.height;
			ray->dish = dis_calcul(data, ray->ra, ray->ry, ray->rx);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			index++;
		}
	}
}

int	check_horizontal_sprite(t_data *data, t_ray_calcul *ray, float Tan)
{
	int	index;
	int	ret;

	index = 0;
	ret = 0;
	ray->dish = 100000;
	if (sin(degtorad(ray->ra)) > 0.001)
		ret = check_up(data, ray, Tan);
	else if (sin(degtorad(ray->ra)) < -0.001)
		ret = check_down(data, ray, Tan);
	else
	{
		ray->rx = data->player_s.pos_x;
		ray->ry = data->player_s.pos_y;
		index = (int)data->map.height;
		ret = UNDEFINED;
	}
	calculate_horizontal_sprite(data, ray, index);
	return (ret);
}

void	calculate_vertical_sprite(t_data *data, t_ray_calcul *ray, int index)
{
	while ((size_t)index < data->map.width)
	{
		ray->mx = (int)(ray->rx) / SQUARE_SIZE;
		ray->my = (int)(ray->ry) / SQUARE_SIZE;
		if (is_within_maps(ray->my, ray->mx, data->map.height, data->map.width)
			&& (is_wall(data->map.map[ray->my][ray->mx])
            || data->map.map[ray->my][ray->mx] == 'P'))
		{
            if (data->map.map[ray->my][ray->mx] == 'P')
                ray->is_sprite_v = 1;
            // ray->rx += ray->xo / 2;
			index = data->map.width;
			ray->disv = dis_calcul(data, ray->ra, ray->ry, ray->rx);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			index++;
		}
	}
}

int	check_vertical_sprite(t_data *data, t_ray_calcul *ray, float Tan)
{
	int	index;
	int	ret;

	index = 0;
	ret = 0;
	ray->disv = 100000;
	if (cos(degtorad(ray->ra)) > 0.001)
		ret = check_right(data, ray, Tan);
	else if (cos(degtorad(ray->ra)) < -0.001)
		ret = check_left(data, ray, Tan);
	else
	{
		ray->rx = data->player_s.pos_x;
		ray->ry = data->player_s.pos_y;
		index = (int)data->map.width;
		ret = UNDEFINED;
	}
	calculate_vertical_sprite(data, ray, index);
	return (ret);
}