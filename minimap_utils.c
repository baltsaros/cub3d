/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:57:45 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/26 15:16:00 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap_values(t_data *data)
{
	data->minimap_s.width = 120;
	data->minimap_s.height = 120;
	data->minimap_s.step = 0.15625;
	data->minimap_s.position.x = data->map.coord[0] + 7;
	data->minimap_s.position.y = data->map.coord[1] + 7;
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
