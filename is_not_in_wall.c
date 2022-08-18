/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_not_in_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:08:12 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/18 16:10:58 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_not_in_wall(t_data *data, int height, int width)
{
    (void)data;
    int i;
    int j;

    i = 0;
    while (i != height)
    {
        j = 0;
        while (j != width)
        {
            if (data->map.map[i][j] == '1')
            {
                printf("Hee heee\n");
            }
            j++;
        }
        i++;
    }
    return (0);
}