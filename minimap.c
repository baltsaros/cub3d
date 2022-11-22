/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/22 15:12:35 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square_coord(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i != PLAYER_SIZE)
	{
		j = 0;
		while (j != PLAYER_SIZE)
		{
			mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_door_coord_h(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	y += SQUARE_SIZE / 8;
	while (i != (SQUARE_SIZE / 4))
	{
		j = 0;
		while (j != SQUARE_SIZE / 2)
		{
			mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_door_coord_v(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	x += SQUARE_SIZE / 8;
	while (i != SQUARE_SIZE / 2)
	{
		j = 0;
		while (j != SQUARE_SIZE / 4)
		{
			mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// track player's direction on the minimap
void	player_dir(t_data *data, int color)
{
	float	x;
	float	y;
	int		j;

	j = 0;
	x = data->player_s.pos_win_x + PLAYER_SIZE / 2;
	y = data->player_s.pos_win_y + PLAYER_SIZE / 2;
	while (j < 20)
	{
		mlx_pixel_put_img(&data->minimap, y, x, color);
		x += data->player_s.delta_x;
		y += data->player_s.delta_y;
		++j;
	}
}

// draw minimap based on player's position; draw a filed 15x15 with a player at the center
void	draw_map(t_data *data, char **map, int color)
{
	int		i;
	int		j;
	int		px;
	int		py;

	px = data->minimap_s.position.x - 7;
	py = data->minimap_s.position.y - 7;
	j = 0;
	while (j != data->minimap_s.height / PLAYER_SIZE)
	{
		i = 0;
		while (i != data->minimap_s.width / PLAYER_SIZE)
		{
	
			if (map[py + j][px + i] && map[py + j][px + i] == '1')
				draw_square_coord(data, color, j * PLAYER_SIZE, i * PLAYER_SIZE);
			else if (i == 7 && j == 7 && map[py + j][px + i])
				draw_square_coord(data, RED, j * PLAYER_SIZE, i * PLAYER_SIZE);
			else if (map[py + j][px + i] && check_charset(map[py + j][px + i], "0NEWS"))
				draw_square_coord(data, GRAY, j * PLAYER_SIZE, i * PLAYER_SIZE);
			++i;
		}
		++j;
	}
	player_dir(data, RED);
}

// copy str with a certain offset
char	*memcpy_offset(void *dest, const void *src, size_t n, size_t offset)
{
	size_t	i;
	char	*src_ch;
	char	*dest_ch;

	if (dest == src)
		return (dest);
	src_ch = (char *)src;
	dest_ch = (char *)dest;
	if (!dest || !src)
		return (0);
	i = 0;
	while (n > i)
	{
		dest_ch[i + offset] = src_ch[i];
		++i;
	}
	return (dest);
}

void	init_minimap_values(t_data *data)
{
	size_t	i;
	size_t	len;
	
	data->minimap_s.width = 120;
	data->minimap_s.height = 120;
	data->minimap_s.step = 0.15625;
	data->minimap_s.position.x = data->map.coord[0] + 7;
	data->minimap_s.position.y = data->map.coord[1] + 7;
	data->minimap_s.mmap = cub_malloc(sizeof(char *) * (data->map.height + 15), data);
	i = 0;
	while (i < data->map.height + 14)
	{
		data->minimap_s.mmap[i] = ft_calloc(data->map.width + 15, 1);
		alloc_check_small(data->minimap_s.mmap[i], data);
		data->minimap_s.mmap[i] = ft_memset(data->minimap_s.mmap[i], ' ', data->map.width + 14);
		++i;
	}
	i = 0;
	while (data->map.map[i])
	{
		len = ft_strlen(data->map.map[i]);
		data->minimap_s.mmap[i + 7] = memcpy_offset(data->minimap_s.mmap[i + 7], data->map.map[i], len, 7);
		++i;
	}
	data->minimap_s.mmap[data->map.height + 14] = NULL;
	print_map(data, data->minimap_s.mmap);
}
