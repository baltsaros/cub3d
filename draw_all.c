/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/13 11:10:07 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int draw_all(t_data *data)
{
	int		ret;

	ret = 0;
	data->ceiling.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT / 2);
	if (data->ceiling.img_ptr != NULL)
		init_ceiling(data);
	else
		return (1);
	data->floor.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT / 2);
	if (data->floor.img_ptr != NULL)
		init_floor(data);
	else
		return (1);
	ret = init_wall(data);
	if (ret != 0)
		return (ret);
	init_player(data);
	init_minimap(data, data->minimap_s);
	return (ret);
}
