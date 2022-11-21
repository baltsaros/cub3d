/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:14:04 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/18 18:15:09 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dis_calcul(t_data *data, float ra, float ry, float rx)
{
	float	dis;
	float	first;
	float	second;

	first = cos(degtorad(ra)) * (rx - data->player_s.pos_x);
	second = sin(degtorad(ra)) * (ry - data->player_s.pos_y);
	dis = first - second;
	return (dis);
}