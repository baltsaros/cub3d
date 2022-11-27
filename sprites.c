/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:28:39 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 22:44:30 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_sprites_textures(t_data *data)
{
    data->sprite_1.img.img_ptr = mlx_xpm_file_to_image(data->mlx,
            "./textures/sprite_1.xpm",
			&data->sprite_1.width, &data->sprite_1.height);
	data->sprite_2.img.img_ptr = mlx_xpm_file_to_image(data->mlx,
            "./textures/sprite_2.xpm",
			&data->sprite_2.width, &data->sprite_2.height);
	data->sprite_3.img.img_ptr = mlx_xpm_file_to_image(data->mlx,
            "./textures/sprite_3.xpm",
			&data->sprite_3.width, &data->sprite_3.height);
    if (!data->sprite_1.img.img_ptr || !data->sprite_2.img.img_ptr
		|| !data->sprite_3.img.img_ptr)
		return (ERROR_TEXT_PTR);
    data->sprite_1.img.addr = mlx_get_data_addr(data->sprite_1.img.img_ptr,
			&data->sprite_1.img.bpp, &data->sprite_1.img.line_length,
			&data->sprite_1.img.endian);
	data->sprite_2.img.addr = mlx_get_data_addr(data->sprite_2.img.img_ptr,
			&data->sprite_2.img.bpp, &data->sprite_2.img.line_length,
			&data->sprite_2.img.endian);
	data->sprite_3.img.addr = mlx_get_data_addr(data->sprite_3.img.img_ptr,
			&data->sprite_3.img.bpp, &data->sprite_3.img.line_length,
			&data->sprite_3.img.endian);
    return (EXIT_SUCCESS);
}

void	init_obj_pos(t_data *data, t_object *soldier)
{
	int	y;
	int	x;

	y = 0;
	while ((size_t)y < data->map.height)
	{
		x = 0;
		while ((size_t)x < data->map.width)
		{
			if (data->map.map[y][x] == 'P')
			{
				soldier->pos.y = y;
				soldier->pos.x = x;
				soldier->fpos.y = (y * SQUARE_SIZE) + (SQUARE_SIZE / 2);
				soldier->fpos.x = (x * SQUARE_SIZE) + (SQUARE_SIZE / 2);
			}
			x++;
		}
		y++;
	}
}

void	draw_sprite(t_data *data, t_text text, t_wall_drawing *wall, t_object *soldier)
{
	int	color;
	
	wall->tx = 0;
	while (wall->begin.x != wall->end.x)
	{
		wall->begin.y = soldier->screen.y - (wall->wallheight / 2);
		wall->ty = 0;
		while (wall->begin.y != wall->end.y)
		{
			color = get_pixel(text.img, (int)wall->ty, (int)wall->tx);
			if (wall->begin.x >= 0 && wall->begin.x < WIDTH && wall->begin.y >= 0 && wall->begin.y < HEIGHT)
				mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y, color);
			wall->begin.y++;
			wall->ty += wall->ty_step;
		}
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
		draw_sprite(data, data->sprite_1, wall, soldier);
	else if (data->anim < 60)
		draw_sprite(data, data->sprite_2, wall, soldier);
	else if (data->anim < 90)
		draw_sprite(data, data->sprite_3, wall, soldier);
}

void	draw_sprites(t_data *data)
{
	t_object	soldier;
	
	init_obj_pos(data, &soldier);
	soldier.fdis.x = soldier.fpos.x - data->player_s.pos_x;
	soldier.fdis.y = soldier.fpos.y - data->player_s.pos_y;
	soldier.distance = sqrt(pow(soldier.fdis.x, 2) + pow(soldier.fdis.y, 2));
	soldier.tmp = (atan2(-soldier.fdis.y, soldier.fdis.x) * (180 / M_PI));
	soldier.tmp = fixang(soldier.tmp);
	soldier.q = data->player_s.p_ang + (FIELD_OF_VIEW / 2) - soldier.tmp;
	if (soldier.tmp > 270 && data->player_s.p_ang < 90)
		soldier.q += 360;
	if (data->player_s.p_ang > 270 && soldier.tmp < 90)
		soldier.q -= 360;
	soldier.screen.x = soldier.q * (WIDTH / FIELD_OF_VIEW);
	soldier.screen.y = (HEIGHT / 2);
	data->wall_drawing.distproj = (WIDTH / 2)
		/ tan(degtorad(FIELD_OF_VIEW / 2));
	data->wall_drawing.wallheight = (SQUARE_SIZE / soldier.distance)
		* data->wall_drawing.distproj;
	init_draw_sprite(data, &soldier, &data->wall_drawing);
}