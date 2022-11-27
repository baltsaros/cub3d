/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:14:04 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 17:46:57 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dis_calcul(t_data *data, float ra, float ry, float rx)
{
	float	x;
	float	y;

	x = cos(degtorad(ra)) * (rx - data->player_s.pos_x);
	y = sin(degtorad(ra)) * (ry - data->player_s.pos_y);
	return (x - y);
}

int	is_within_maps(int my, int mx, int height, int width)
{
	return (my >= 0 && mx >= 0 && my < height && mx < width);
}

int	is_wall(char c)
{
	return (c != '0' && c != 'C' && c != 'P' && is_player(c));
}
