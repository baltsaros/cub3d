/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 19:01:28 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/18 13:28:32 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_img_null(t_data *data)
{
	data->background.img_ptr = NULL;
	data->walls.img_ptr = NULL;
	data->minimap.img_ptr = NULL;
	data->player.img_ptr = NULL;
	data->no_text.img.img_ptr = NULL;
	data->so_text.img.img_ptr = NULL;
	data->ea_text.img.img_ptr = NULL;
	data->we_text.img.img_ptr = NULL;
}

int	init_img(t_data *data)
{
	data->background.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->walls.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->minimap.img_ptr = mlx_new_image(data->mlx,
			data->minimap_s.width, data->minimap_s.height);
	data->player.img_ptr = mlx_new_image(data->mlx, PLAYER_SIZE
			/ 2, PLAYER_SIZE / 2);
	if (!data->background.img_ptr || !data->walls.img_ptr
		|| !data->minimap.img_ptr || !data->player.img_ptr)
		return (1);
	data->background.addr = mlx_get_data_addr(data->background.img_ptr,
			&data->background.bpp, &data->background.line_length,
			&data->background.endian);
	data->walls.addr = mlx_get_data_addr(data->walls.img_ptr,
			&data->walls.bpp, &data->walls.line_length,
			&data->walls.endian);
	data->minimap.basic_color = 0x88000000;
	data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr,
			&data->minimap.bpp, &data->minimap.line_length,
			&data->minimap.endian);
	data->player.basic_color = 0x000000;
	data->player.addr = mlx_get_data_addr(data->player.img_ptr,
			&data->player.bpp, &data->player.line_length,
			&data->player.endian);
	return (0);
}

int	is_xpm(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i] != 'm')
		return (1);
	i--;
	if (i < 0 || str[i] != 'p')
		return (1);
	i--;
	if (i < 0 || str[i] != 'x')
		return (1);
	i--;
	if (i < 0 || str[i] != '.')
		return (1);
	return (0);
}

void	mlx_xpm_init(t_data *data)
{
	data->no_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.no,
			&data->no_text.width, &data->no_text.height);
	data->so_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.so,
			&data->so_text.width, &data->so_text.height);
	data->ea_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.ea,
			&data->ea_text.width, &data->ea_text.height);
	data->we_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.we,
			&data->we_text.width, &data->we_text.height);
}

int	load_textures(t_data *data)
{
	if (is_xpm(data->map.no) || is_xpm(data->map.so)
		|| is_xpm(data->map.ea) || is_xpm(data->map.we))
		return (1);
	mlx_xpm_init(data);
	if (!data->no_text.img.img_ptr || !data->so_text.img.img_ptr
		|| !data->ea_text.img.img_ptr || !data->we_text.img.img_ptr)
		return (1);
	data->no_text.img.addr = mlx_get_data_addr(data->no_text.img.img_ptr,
			&data->no_text.img.bpp, &data->no_text.img.line_length,
			&data->no_text.img.endian);
	data->so_text.img.addr = mlx_get_data_addr(data->so_text.img.img_ptr,
			&data->so_text.img.bpp, &data->so_text.img.line_length,
			&data->so_text.img.endian);
	data->ea_text.img.addr = mlx_get_data_addr(data->ea_text.img.img_ptr,
			&data->ea_text.img.bpp, &data->ea_text.img.line_length,
			&data->ea_text.img.endian);
	data->we_text.img.addr = mlx_get_data_addr(data->we_text.img.img_ptr,
			&data->we_text.img.bpp, &data->we_text.img.line_length,
			&data->we_text.img.endian);
	return (0);
}
