/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:28:39 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/26 19:22:46 by mthiry           ###   ########.fr       */
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

// void	draw_sprite(t_data *data, t_object *soldier, t_wall_drawing *wall)
// {
// }

void	draw_sprites(t_data *data)
{
	t_object	soldier;

	init_obj_pos(data, &soldier);
	soldier.distance = sqrt(pow((soldier.pos.x - data->player_s.pos_x), 2)
		+ pow((soldier.pos.y - data->player_s.pos_y), 2));

	printf("distance: %f\n", soldier.distance);

	data->wall_drawing.distproj = (WIDTH / 2)
		/ tan(degtorad(FIELD_OF_VIEW / 2));
	data->wall_drawing.wallheight = (SQUARE_SIZE / soldier.distance)
		* data->wall_drawing.distproj;

	printf("wallheight: %f\n",  data->wall_drawing.wallheight);
}