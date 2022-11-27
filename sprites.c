/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:28:39 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 01:53:00 by mthiry           ###   ########.fr       */
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
				soldier->fpos.y = (y * SQUARE_SIZE)
					+ (SQUARE_SIZE / 2) - (PSIZE / 2);
				soldier->fpos.x = (x * SQUARE_SIZE)
					+ (SQUARE_SIZE / 2) - (PSIZE / 2);
				break ;
			}
			x++;
		}
		y++;
	} 
}

void	draw_vertical_sprite(t_data *data, t_wall_drawing *wall,
		t_ray_calcul *ray)
{
	wall->begin.x = (float)ray->r;
	wall->begin.y = (HEIGHT / 2)
		- (wall->wallheight / 2);
	wall->end.x = wall->begin.x;
	wall->end.y = wall->begin.y
		+ wall->wallheight;
	wall->ty = 0;
	wall->ty_step = (float)data->sprite_1.height / (float)wall->wallheight;
	wall->tx = (int)(ray->rx) % data->sprite_1.width;
	draw_a_wall(data, wall, data->sprite_1);
}

void	draw_sprites(t_data *data, t_wall_drawing wall,
		t_ray_calcul ray)
{
	t_object	soldier;

	init_obj_pos(data, &soldier);
	soldier.dis_x = soldier.fpos.x - data->player_s.pos_x;
	soldier.dis_y = soldier.fpos.y - data->player_s.pos_y;
	soldier.distance = sqrt(pow(soldier.dis_x, 2) + pow(soldier.dis_y, 2));
	wall.wallheight = (SQUARE_SIZE / soldier.distance)
		* data->distProj;
	ray.r = 0;
	ray.ra = fixang(data->player_s.p_ang + 30);
	while (ray.r < WIDTH)
	{	
		cast_ray_in_dir(data, &ray, &soldier, (1.0 / tan(degtorad(ray.ra))));
		if (ray.my == soldier.pos.y && ray.mx == soldier.pos.x)
			draw_vertical_sprite(data, &wall, &ray);
		ray.ra = fixang(ray.ra - ((float)FIELD_OF_VIEW / (float)WIDTH));
		ray.r++;
	}
}