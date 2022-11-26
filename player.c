/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/26 15:29:58 by abuzdin          ###   ########.fr       */
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
	data->player_s.speed = 12;
	x = (data->player_s.speed * 100) / SQUARE_SIZE;
	// printf("step: %d\n", data->player_s.speed);
	data->minimap_s.step = (1 * x) / 100;
	// printf("x:%f\nmspeed: %f\n", x, data->minimap_s.step);
	data->player_s.rot_speed = 5;
	data->player_s.pos_win_x = data->minimap_s.width / 2 - PSIZE / 2;
	data->player_s.pos_win_y = data->minimap_s.height / 2 - PSIZE / 2;
}
