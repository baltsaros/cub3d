/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 17:53:49 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_background(t_data *data)
{
	int		color_ceiling;
	int		color_floor;
	t_point	begin;
	t_point	end;

	color_ceiling = create_trgb(0, data->map.ceiling[0],
			data->map.ceiling[1], data->map.ceiling[2]);
	color_floor = create_trgb(0, data->map.floor[0],
			data->map.floor[1], data->map.floor[2]);
	// color_ceiling = create_trgb(0,
	// 		ft_atoi(data->map.c_spl[0]),
	// 		ft_atoi(data->map.c_spl[1]),
	// 		ft_atoi(data->map.c_spl[2]));
	// color_floor = create_trgb(0,
	// 		ft_atoi(data->map.f_spl[0]),
	// 		ft_atoi(data->map.f_spl[1]),
	// 		ft_atoi(data->map.f_spl[2]));
	begin.x = 0;
	begin.y = HEIGHT / 2;
	end.x = WIDTH;
	end.y = HEIGHT;
	draw_square(data->background, color_ceiling, HEIGHT / 2, WIDTH);
	draw_square_from(data->background, color_floor, begin, end);
}

int	draw_all(t_data *data)
{
	ft_memset(data->walls.addr, create_trgb(255, 255, 255, 255),
		HEIGHT * WIDTH * sizeof(int));
	ft_memset(data->minimap.addr, create_trgb(255, 255, 255, 255),
		(data->minimap_s.height + 16) * (data->minimap_s.width + 16)
		* sizeof(int));
	draw_map(data, data->minimap_s.mmap, data->minimap.basic_color);

	data->anim++;
	if (data->anim > 90)
		data->anim = 0;

	raycast(data, data->ray_calcul);
	raycast_sprites(data, data->ray_calcul);

	mlx_put_image_to_window(data->mlx, data->win,
		data->background.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr,
		10, 10);
	return (0);
}
