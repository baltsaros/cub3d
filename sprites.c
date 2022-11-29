/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:28:39 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/29 15:04:57 by mthiry           ###   ########.fr       */
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

int	init_depth(t_data *data)
{
	int	i;

	i = 0;
	data->depth = (int *) malloc (WIDTH * sizeof(int));
	if (!data->depth)
		return (ERROR_FAILED_M);
	while (i != WIDTH)
	{
		data->depth[i] = 0;
		i++;
	}
	data->is_depth_allocated = 1;
	return (EXIT_SUCCESS);
}

void	draw_a_sprite(t_data *data, t_object obj)
{
	obj.tmp = (atan2(-obj.fdis.y, obj.fdis.x) * (180 / M_PI));
	obj.tmp = fixang(obj.tmp);
	obj.q = data->player_s.p_ang + (FIELD_OF_VIEW / 2) - obj.tmp;
	if (obj.tmp > 270 && data->player_s.p_ang < 90)
		obj.q += 360;
	if (data->player_s.p_ang > 270 && obj.tmp < 90)
		obj.q -= 360;
	obj.screen.x = obj.q * (WIDTH / FIELD_OF_VIEW);
	obj.screen.y = (HEIGHT / 2);
	data->wall_drawing.distproj = (WIDTH / 2)
		/ tan(degtorad(FIELD_OF_VIEW / 2));
	data->wall_drawing.wallheight = (SQUARE_SIZE / obj.distance)
		* data->wall_drawing.distproj;
	init_draw_sprite(data, &obj, &data->wall_drawing);
}
