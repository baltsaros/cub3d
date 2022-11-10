/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/10 11:20:06 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_img img, int color, int end_i, int end_j)
{
	int i;
	int j;

	i = 0;
	while (i != end_i)
	{
		j = 0;
		while (j != end_j)
		{
			mlx_pixel_put_img(&img, j, i, color);
			j++;
		}
		i++;
	}
}

void	init_ceiling(t_data *data)
{
	data->ceiling.basic_color = create_trgb(0,
		ft_atoi(data->map.c_spl[0]),
		ft_atoi(data->map.c_spl[1]),
		ft_atoi(data->map.c_spl[2]));
	data->ceiling.addr = mlx_get_data_addr(data->ceiling.img_ptr, &data->ceiling.bpp,
		&data->ceiling.line_length, &data->ceiling.endian);
}

void	init_floor(t_data *data)
{
	data->floor.basic_color = create_trgb(0,
		ft_atoi(data->map.f_spl[0]),
		ft_atoi(data->map.f_spl[1]),
		ft_atoi(data->map.f_spl[2]));
	data->floor.addr = mlx_get_data_addr(data->floor.img_ptr, &data->floor.bpp,
		&data->floor.line_length, &data->floor.endian);
}

int		draw_all(t_data *data)
{

	draw_square(data->ceiling, data->ceiling.basic_color, HEIGHT / 2, WIDTH);
	mlx_put_image_to_window(data->mlx, data->win, data->ceiling.img_ptr, 0, 0);
	draw_square(data->floor, data->floor.basic_color, HEIGHT / 2, WIDTH);
	mlx_put_image_to_window(data->mlx, data->win, data->floor.img_ptr, 0, HEIGHT / 2);
	// printf("minimap\n");
	init_minimap(data, data->minimap_s);
	// printf("player\n");
	init_player(data);
	// printf("ray\n");
	init_ray(data);
	// render(data);
	// usleep(1000);
	return (0);
}
