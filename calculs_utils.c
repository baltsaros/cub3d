/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:30:54 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/29 18:02:21 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float   degToRad(int a)
{
    return (a * M_PI / 180.0);
}

float FixAng(float a)
{ 
    if(a > 359)
        a -= 360;
    if(a < 0)
        a += 360;
    return a;
}