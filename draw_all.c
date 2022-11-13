/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/13 19:20:13 by mthiry           ###   ########.fr       */
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

int draw_all(t_data *data)
{
	int		ret;

	ret = 0;
	// init_background(data);
	ret = init_wall(data);
	if (ret != 0)
		return (ret);
	// init_minimap(data, data->minimap_s);
	// init_player(data);
	// mlx_put_image_to_window(data->mlx, data->win, data->background.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
	return (ret);
}
