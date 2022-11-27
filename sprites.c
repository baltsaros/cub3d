/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:28:39 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 17:53:46 by mthiry           ###   ########.fr       */
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

int	adapt_distance_sprite(t_ray_calcul *ray, int posH, int posV)
{
	if (ray->disv < ray->dish)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->dish = ray->disv;
		ray->is_sprite_h = ray->is_sprite_v;
		return (posV);
	}
	return (posH);
}

void	draw_vertical_sprite(t_data *data, t_wall_drawing *wall,
		t_ray_calcul *ray, int pos)
{
	wall->ty = 0;
	wall->ty_step = (float)data->sprite_1.height / (float)wall->wallheight;
	if (pos == NORTH || pos == SOUTH)
		wall->tx = (int)(ray->rx) % data->sprite_1.width;
	else
		wall->tx = (int)(ray->ry) % data->sprite_1.width;
	if (data->anim < 30)
		draw_a_wall(data, wall, data->sprite_1);
	else if (data->anim < 60)
		draw_a_wall(data, wall, data->sprite_2);
	else if (data->anim < 90)
		draw_a_wall(data, wall, data->sprite_3);
}

void	init_calculate_sprite(t_data *data, t_ray_calcul *ray, int pos)
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
	draw_vertical_sprite(data, &data->wall_drawing, ray, pos);
}

void	raycast_sprites(t_data *data, t_ray_calcul ray)
{
	float	tan_c;
	int		posh;
	int		posv;
	int		pos;

	ray.r = 0;
	ray.ra = fixang(data->player_s.p_ang + 30);
	while (ray.r < WIDTH)
	{
		ray.is_sprite_h = 0;
		ray.is_sprite_v = 0;
		tan_c = tan(degtorad(ray.ra));
		posv = check_vertical_sprite(data, &ray, tan_c);
		ray.vx = ray.rx;
		ray.vy = ray.ry;
		posh = check_horizontal_sprite(data, &ray, (1.0 / tan_c));
		pos = adapt_distance_sprite(&ray, posh, posv);
		fisheye_fix(data, &ray);
		if (ray.is_sprite_h)
			init_calculate_sprite(data, &ray, pos);
		ray.ra = fixang(ray.ra - ((float)FIELD_OF_VIEW / (float)WIDTH));
		ray.r++;
	}
}