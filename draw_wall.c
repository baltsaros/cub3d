/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:18:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/13 19:30:50 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_a_wall(t_data *data, t_wall_drawing *wall, t_text text, double shade)
{
    int     color;
    
    while (wall->begin.y != wall->end.y + 1)
    {
        if (wall->begin.x >= 0 && wall->begin.x <= WIDTH && wall->begin.y >= 0 && wall->begin.y <= HEIGHT)
        {
            color = get_pixel(text.img, (int)wall->ty, (int)wall->tx);
            mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y, color * shade);
        }    
        wall->begin.y++;
        wall->ty += wall->ty_step;
    }
}

void    draw_vertical_line(t_data *data, t_wall_drawing *wall, t_ray_calcul *ray, int pos)
{   
    wall->ty = 0;
    if (pos == NORTH)
    {
        wall->ty_step = (float)data->no_text.height / (float)wall->wallHeight;
        wall->tx = (int)(ray->rx) % data->no_text.width;
        draw_a_wall(data, wall, data->no_text, 1);
    }
    else if (pos == SOUTH)
    {
        wall->ty_step = (float)data->so_text.height / (float)wall->wallHeight;
        wall->tx = (int)(ray->rx) % data->so_text.width;
        draw_a_wall(data, wall, data->so_text, 1);
    }
    else if (pos == EAST)
    {
        wall->ty_step = (float)data->ea_text.height / (float)wall->wallHeight;
        wall->tx = (int)(ray->ry) % data->ea_text.width;
        draw_a_wall(data, wall, data->ea_text, 1);
    }
    else if (pos == WEST)
    {
        wall->ty_step = (float)data->we_text.height / (float)wall->wallHeight;
        wall->tx = (int)(ray->ry) % data->we_text.width;
        draw_a_wall(data, wall, data->we_text, 1);
    }
}

void	init_calculate_wall(t_data *data, t_ray_calcul *ray, int pos)
{
    data->wall_drawing.distProj = (WIDTH / 2) / tan(degToRad(FIELD_OF_VIEW / 2));
    data->wall_drawing.wallHeight = (SQUARE_SIZE / ray->disH) * data->wall_drawing.distProj;
    data->wall_drawing.begin.x = (float)ray->r;
    data->wall_drawing.begin.y = (HEIGHT / 2) - (data->wall_drawing.wallHeight / 2);
    data->wall_drawing.end.x = data->wall_drawing.begin.x;
    data->wall_drawing.end.y = data->wall_drawing.begin.y + data->wall_drawing.wallHeight;
    draw_vertical_line(data, &data->wall_drawing, ray, pos);
}