/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 23:52:04 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/28 13:28:08 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite_y(t_data *data, t_text text, t_wall_drawing *wall, t_object *soldier)
{
    int color;
    
    if (wall->begin.y < 0)
	{
		wall->ty = (-wall->begin.y * wall->ty_step);
		wall->begin.y = 0;
	}
    while (wall->begin.y != wall->end.y
		&& soldier->distance < data->depth[wall->begin.x]
        && wall->begin.y <= HEIGHT)
	{
		color = get_pixel(text.img, (int)wall->ty, (int)wall->tx);
		if (wall->begin.x >= 0 && color >= 0)
			mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y, color);
		wall->begin.y++;
		wall->ty += wall->ty_step;
	}
}

void	draw_sprite_x(t_data *data, t_text text, t_wall_drawing *wall, t_object *soldier)
{	
	wall->tx = 0;
	while (wall->begin.x != wall->end.x && wall->begin.x <= WIDTH)
	{
		wall->begin.y = soldier->screen.y - (wall->wallheight / 2);
		wall->ty = 0;
		draw_sprite_y(data, text, wall, soldier);
		wall->begin.x++;
		wall->tx += wall->tx_step;
	}
}

void	init_draw_sprite(t_data *data, t_object	*soldier, t_wall_drawing *wall)
{
	wall->end.y = soldier->screen.y + (wall->wallheight / 2);
	wall->begin.x = soldier->screen.x - (wall->wallheight / 2);
	wall->end.x = soldier->screen.x + (wall->wallheight / 2);
	wall->tx_step = (float)data->sprite_1.width / (float)wall->wallheight;
	wall->ty_step = (float)data->sprite_1.height / (float)wall->wallheight;
	if (data->anim < 30)
		draw_sprite_x(data, data->sprite_1, wall, soldier);
	else if (data->anim < 60)
		draw_sprite_x(data, data->sprite_2, wall, soldier);
	else if (data->anim < 90)
		draw_sprite_x(data, data->sprite_3, wall, soldier);
}