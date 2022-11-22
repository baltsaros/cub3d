/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 22:18:43 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/23 00:39:41 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_close(t_data *data, int my, int mx)
{
	int	py;
	int	px;

	py = data->player_s.pos_y / SQUARE_SIZE;
	px = data->player_s.pos_x / SQUARE_SIZE;
	if (py == my - 1 && px == mx)
		return (1);
	if (py == my + 1 && px == mx)
		return (1);
	if (py == my && px == mx - 1)
		return (1);
	if (py == my && px == mx + 1)
		return (1);
	return (0);
}

int	is_door(t_data *data, t_ray_calcul *ray)
{
	int	my;
	int	mx;

	my = ray->ry / SQUARE_SIZE;
	mx = ray->rx / SQUARE_SIZE;
	if (ray->is_door_h && ray->dish < SQUARE_SIZE)
	{
		if (data->map.map[my][mx] == 'D' && is_close(data, my, mx))
		{
			data->map.map[my][mx] = 'C';
			return (1);
		}
		if (data->map.map[my][mx] == 'C' && is_close(data, my, mx))
		{
			data->map.map[my][mx] = 'D';
			return (1);
		}
	}
	return (0);
}

void	open_close_door(t_data *data, t_ray_calcul ray)
{
	float	tan_c;
	int		posh;
	int		posv;

	ray.r = 0;
	ray.ra = fixang(data->player_s.p_ang + ((FIELD_OF_VIEW / 6) / 2));
	while (ray.r < WIDTH / 2)
	{
		ray.is_door_h = 0;
		ray.is_door_v = 0;
		tan_c = tan(degtorad(ray.ra));
		posv = check_vertical_wall(data, &ray, tan_c);
		ray.vx = ray.rx;
		ray.vy = ray.ry;
		posh = check_horizontal_wall(data, &ray, (1.0 / tan_c));
		adapt_distance(&ray, posh, posv);
		ray.ra = fixang(ray.ra - ((float)FIELD_OF_VIEW / (float)WIDTH));
		ray.r++;
		if (is_door(data, &ray))
			break ;
	}
}
