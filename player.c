/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/26 17:50:11 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

void	init_player_values(t_data *data)
{
	float	x;

	data->player_s.pos_x = 0;
	data->player_s.pos_y = 0;
	data->player_s.p_ang = data->map.angle;
	data->player_s.delta_x = cos(degtorad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degtorad(data->player_s.p_ang));
	data->player_s.pos_y = (data->map.coord[1] * SQUARE_SIZE)
		+ (SQUARE_SIZE / 2) - (PSIZE / 2);
	data->player_s.pos_x = (data->map.coord[0] * SQUARE_SIZE)
		+ (SQUARE_SIZE / 2) - (PSIZE / 2);
	data->player_s.speed = 9;
	x = ((float)data->player_s.speed * 100.0) / SQUARE_SIZE;
	data->minimap_s.step = (1 * x) / 100;
	data->player_s.rot_speed = 5;
	data->player_s.pos_win_x = data->minimap_s.width / 2 - PSIZE / 2;
	data->player_s.pos_win_y = data->minimap_s.height / 2 - PSIZE / 2;
}
