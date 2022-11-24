/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:14:04 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/24 08:14:06 by abuzdin          ###   ########.fr       */
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
