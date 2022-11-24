/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:18:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/24 15:04:34 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_a_wall(t_data *data, t_wall_drawing *wall,
		t_text text)
{
	int	color;

	if (wall->begin.y < 0)
	{
		wall->ty = (-wall->begin.y * wall->ty_step);
		wall->begin.y = 0;
	}
	while (wall->begin.y != wall->end.y && wall->begin.y <= HEIGHT)
	{
		color = get_pixel(text.img, (int)wall->ty, (int)wall->tx);
		mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y,
			color);
		wall->begin.y++;
		wall->ty += wall->ty_step;
	}
}

void	draw_vertical_line(t_data *data, t_wall_drawing *wall,
		t_ray_calcul *ray, int pos)
{
	wall->ty = 0;
	if (pos == NORTH)
	{
		wall->ty_step = (float)data->no_text.height / (float)wall->wallheight;
		wall->tx = (int)(ray->rx) % data->no_text.width;
		draw_a_wall(data, wall, data->no_text);
	}
	else if (pos == SOUTH)
	{
		wall->ty_step = (float)data->so_text.height / (float)wall->wallheight;
		wall->tx = (int)(ray->rx) % data->so_text.width;
		draw_a_wall(data, wall, data->so_text);
	}
	else if (pos == EAST)
	{
		wall->ty_step = (float)data->ea_text.height / (float)wall->wallheight;
		wall->tx = (int)(ray->ry) % data->ea_text.width;
		draw_a_wall(data, wall, data->ea_text);
	}
	else if (pos == WEST)
	{
		wall->ty_step = (float)data->we_text.height / (float)wall->wallheight;
		wall->tx = (int)(ray->ry) % data->we_text.width;
		draw_a_wall(data, wall, data->we_text);
	}
}

void	draw_vertical_door(t_data *data, t_wall_drawing *wall,
		t_ray_calcul *ray, int pos)
{
	wall->ty = 0;
	wall->ty_step = (float)data->door_text.height / (float)wall->wallheight;
	if (pos == NORTH || pos == SOUTH)
		wall->tx = (int)(ray->rx) % data->door_text.width;
	else
		wall->tx = (int)(ray->ry) % data->door_text.width;
	draw_a_wall(data, wall, data->door_text);
}

void	init_calculate_wall(t_data *data, t_ray_calcul *ray, int pos)
{
	data->wall_drawing.distproj = (WIDTH / 2)
		/ tan(degtorad(FIELD_OF_VIEW / 2));
	data->wall_drawing.wallheight = (SQUARE_SIZE / ray->dish)
		* data->wall_drawing.distproj;
	data->wall_drawing.begin.x = (float)ray->r;
	data->wall_drawing.begin.y = (HEIGHT / 2)
		- (data->wall_drawing.wallheight / 2);
	data->wall_drawing.end.x = data->wall_drawing.begin.x;
	data->wall_drawing.end.y = data->wall_drawing.begin.y
		+ data->wall_drawing.wallheight;
	if (ray->is_door_h)
		draw_vertical_door(data, &data->wall_drawing, ray, pos);
	else
		draw_vertical_line(data, &data->wall_drawing, ray, pos);
}
