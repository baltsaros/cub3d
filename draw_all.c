/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/21 15:00:17 by mthiry           ###   ########.fr       */
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
	data->is_full_screen = 0;
	ft_memset(data->walls.addr, create_trgb(255, 255, 255, 255),
		HEIGHT * WIDTH * sizeof(int));
	raycast(data, data->ray_calcul);
	ft_memset(data->minimap.addr, create_trgb(255, 255, 255, 255),
		data->minimap_s.height * data->minimap_s.width * sizeof(int));
	draw_map(data, data->minimap.basic_color, data->map.height,
		data->map.width);
	ft_memset(data->player.addr, data->player.basic_color,
		PLAYER_SIZE * sizeof(int));
	if (data->is_full_screen != WIDTH)
	{
		init_background(data);
		mlx_put_image_to_window(data->mlx, data->win,
			data->background.img_ptr, 0, 0);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr,
		data->minimap_s.position.x, data->minimap_s.position.y);
	mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr,
		data->player_s.pos_win_x, data->player_s.pos_win_y);
	return (0);
}
