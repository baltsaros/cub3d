/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 17:46:17 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square_coord(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i != PSIZE)
	{
		j = 0;
		while (j != PSIZE)
		{
			mlx_pixel_put_img(&data->minimap, y + i, x + j, color);
			j++;
		}
		i++;
	}
}

void	draw_mm_background(t_data *data, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j != data->minimap_s.height + 16)
	{
		i = 0;
		while (i != data->minimap_s.width + 16)
		{
			mlx_pixel_put_img(&data->minimap, i, j, color);
			i++;
		}
		j++;
	}
}

// track player's direction on the minimap
void	draw_dir(t_data *data, int color)
{
	float	x;
	float	y;
	int		j;

	j = 0;
	x = data->player_s.pos_win_x + PSIZE / 2;
	y = data->player_s.pos_win_y + PSIZE / 2;
	while (j < 20)
	{
		mlx_pixel_put_img(&data->minimap, x, y, color);
		x += data->player_s.delta_x;
		y += data->player_s.delta_y;
		++j;
	}
}

// draw minimap based on player's position;
// draw a filed 15x15 with a player at the center
void	draw_map(t_data *data, char **map, int color)
{
	int		j;
	int		px;
	int		py;

	px = lroundf(data->minimap_s.position.x) - 7;
	py = lroundf(data->minimap_s.position.y) - 7;
	draw_mm_background(data, DPURPLE);
	j = 1;
	while (j != (data->minimap_s.height + 8) / PSIZE)
	{
		data->i = 1;
		while ((int)data->i != (data->minimap_s.width + 8) / PSIZE)
		{
			if (map[py + j][px + data->i] && map[py + j][px + data->i] == '1')
				draw_square_coord(data, color, j * PSIZE, data->i * PSIZE);
			else if (data->i == 7 && j == 7 && map[py + j][px + data->i])
				draw_square_coord(data, RED, j * PSIZE, data->i * PSIZE);
			else if (map[py + j][px + data->i]
				&& check_charset(map[py + j][px + data->i], "0NEWSP"))
				draw_square_coord(data, GRAY, j * PSIZE, data->i * PSIZE);
			++data->i;
		}
		++j;
	}
	draw_dir(data, RED);
}

void	init_minimap(t_data *data)
{
	size_t	i;
	size_t	len;
	char	**tmp;

	init_minimap_values(data);
	tmp = cub_malloc(sizeof(char *) * (data->map.height + 15), data);
	i = 0;
	while (i < data->map.height + 14)
	{
		tmp[i] = ft_calloc(data->map.width + 15, 1);
		alloc_check_small(tmp[i], data);
		tmp[i] = ft_memset(tmp[i], ' ', data->map.width + 14);
		++i;
	}
	i = 0;
	while (data->map.map[i])
	{
		len = ft_strlen(data->map.map[i]);
		tmp[i + 7] = memcpy_offset(tmp[i + 7], data->map.map[i], len, 7);
		++i;
	}
	tmp[data->map.height + 14] = NULL;
	data->minimap_s.mmap = tmp;
}
