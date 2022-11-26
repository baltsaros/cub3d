/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:28:39 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/26 17:40:15 by mthiry           ###   ########.fr       */
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
				soldier->pos.y = (y * SQUARE_SIZE)
					+ (SQUARE_SIZE / 2) - (PSIZE / 2);
				soldier->pos.x = (x * SQUARE_SIZE)
					+ (SQUARE_SIZE / 2) - (PSIZE / 2);
				break ;
			}
			x++;
		}
		y++;
	} 
}

void	draw_sprite(t_data *data, t_object *soldier, t_wall_drawing *wall)
{
	int	x;
	int	y;
	
	x = soldier->sx - soldier->scale;
	y = 0;
	wall->tx = 0;
	wall->ty_step = (float)(SQUARE_SIZE / 2) / (float)soldier->scale;
	wall->tx_step = ((float)(SQUARE_SIZE / 2) - 0.5) / (float)soldier->scale;

	int	color = 0xFFC0CB;

	printf("sx: %f\n", soldier->sx);
	printf("sy: %f\n", soldier->sy);
	printf("scale: %d\n", soldier->scale);
	printf("x: %d\n", x);

	while (x < soldier->sx + soldier->scale)
	{
		wall->ty = (float)(SQUARE_SIZE / 2) - 1.0;
		y = 0;
		while (y < soldier->scale)
		{
			mlx_pixel_put_img(&data->walls, x, y, color);
			wall->ty -= wall->ty_step;
			if (wall->ty < 0)
				wall->ty = 0;
			y++;
		}
		wall->tx += wall->tx_step;
		x++;
	}
}

void	draw_sprites(t_data *data, t_wall_drawing wall)
{
	t_object	soldier;

	init_obj_pos(data, &soldier);
	soldier.z = 20;
	soldier.sx = soldier.pos.x;
	soldier.sy = soldier.pos.y;
	soldier.sz = soldier.z;
	soldier.cs = cos(degtorad(data->player_s.p_ang));
	soldier.sn = sin(degtorad(data->player_s.p_ang));
	soldier.a = soldier.sy * soldier.cs + soldier.sx * soldier.sn;
	soldier.b =  soldier.sx * soldier.cs - soldier.sy * soldier.sn;
	soldier.sx = soldier.a;
	soldier.sy = soldier.b;
	soldier.sx = (soldier.sx * 108.0 / soldier.sy) + (WIDTH / 2);
	soldier.sy = (soldier.sz * 108.0 / soldier.sy) + (HEIGHT / 2);
	soldier.scale = (SQUARE_SIZE / 2) * HEIGHT / soldier.b;
	if (soldier.scale < 0)
		soldier.scale = 0;
	if (soldier.scale > WIDTH)
		soldier.scale = WIDTH;
	draw_sprite(data, &soldier, &wall);
}