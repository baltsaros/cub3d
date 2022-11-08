/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:30:54 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/08 17:54:03 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float   degToRad(float a)
{
    return (a * (float)M_PI / 180.0);
}

float FixAng(float a)
{ 
    if(a > 180)
        a -= 360;
    if(a <= -180)
        a += 360;
    return (a);
}

// float FixAng(float a)
// { 
//     if(a > 359)
//         a -= 360;
//     if(a < 0)
//         a += 360;
//     return (a);
// }