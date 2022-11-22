/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/22 15:02:59 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_background(t_data *data)
{
	int		color_ceiling;
	int		color_floor;
	t_point	begin;
	t_point	end;

	color_ceiling = create_trgb(0,
			ft_atoi(data->map.c_spl[0]),
			ft_atoi(data->map.c_spl[1]),
			ft_atoi(data->map.c_spl[2]));
	color_floor = create_trgb(0,
			ft_atoi(data->map.f_spl[0]),
			ft_atoi(data->map.f_spl[1]),
			ft_atoi(data->map.f_spl[2]));
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
		data->minimap_s.height * data->minimap_s.width * sizeof(int));
	draw_map(data, data->minimap_s.mmap, data->minimap.basic_color);
	raycast(data, data->ray_calcul);
	mlx_put_image_to_window(data->mlx, data->win,
		data->background.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr,
		10, 10);
	// mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr,
	// 	data->player_s.pos_win_x + 10, data->player_s.pos_win_y + 10);
	return (0);
}
