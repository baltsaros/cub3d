/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:23:44 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/08 17:05:20 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_pixel(t_img img, int y, int x)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bpp / 8));
	return (*(unsigned int *)dst);
}

void	mlx_pixel_put_img(t_img	*img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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
