/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:30:54 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/19 14:32:17 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float   degToRad(int a)
{
    return (a * M_PI / 180.0);
}

int FixAng(int a)
{ 
    if(a > 359)
        a -= 360;
    if(a < 0)
        a += 360;
    return a;
}