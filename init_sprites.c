/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:20:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/29 15:12:04 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_nbr_objs(t_data *data)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while ((size_t)y < data->map.height)
	{
		x = 0;
		while ((size_t)x < data->map.width)
		{
			if (data->map.map[y][x] == 'P')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	init_obj_pos(t_data *data)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	while ((size_t)y < data->map.height)
	{
		x = 0;
		while ((size_t)x < data->map.width)
		{
			if (data->map.map[y][x] == 'P')
			{
				data->objs[i].pos.y = y;
				data->objs[i].pos.x = x;
				data->objs[i].fpos.y = (y * SQUARE_SIZE)
					+ (SQUARE_SIZE / 2);
				data->objs[i].fpos.x = (x * SQUARE_SIZE)
					+ (SQUARE_SIZE / 2);
				i++;
			}
			x++;
		}
		y++;
	}
}

void	draw_sprites(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_objs == i)
		return ;
	while (i < data->nb_objs)
	{
		data->objs[i].fdis.x = data->objs[i].fpos.x - data->player_s.pos_x;
		data->objs[i].fdis.y = data->objs[i].fpos.y - data->player_s.pos_y;
		data->objs[i].distance = sqrt(pow(data->objs[i].fdis.x, 2)
				+ pow(data->objs[i].fdis.y, 2));
		i++;
	}
	quicksort(data, data->quick, 0, data->nb_objs - 1);
	i = data->nb_objs - 1;
	while (i >= 0)
	{
		draw_a_sprite(data, data->objs[i]);
		i--;
	}
}

int	init_sprites(t_data *data)
{
	data->nb_objs = init_nbr_objs(data);
	if (data->nb_objs == 0)
		return (EXIT_SUCCESS);
	data->objs = malloc (data->nb_objs * sizeof(t_object));
	if (!data->objs)
		return (ERROR_FAILED_M);
	data->is_objs_allocated = 1;
	init_obj_pos(data);
	return (EXIT_SUCCESS);
}
