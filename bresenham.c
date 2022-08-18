/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:47:55 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/18 16:34:36 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_pixel_put_img(t_img	*img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_bre_values(t_bre	*values, t_seg *seg)
{
	values->dx = abs (seg->x1 - seg->x0);
	if (seg->x0 < seg->x1)
		values->sx = 1;
	else
		values->sx = -1;
	values->dy = -abs (seg->y1 - seg->y0);
	if (seg->y0 < seg->y1)
		values->sy = 1;
	else
		values->sy = -1;
	values->err = values->dx + values->dy;
}

void	ft_put_pixel(t_seg *seg, t_img *img, int color)
{
	if ((seg->x0 < WIDTH && seg->y0 < HEIGHT)
		&& (seg->x0 >= 0 && seg->y0 >= 0))
		mlx_pixel_put_img(img, seg->x0, seg->y0, color);
}

void	init_seg_values(t_seg *seg, t_point *begin, t_point *end)
{
	seg->x0 = begin->x;
	seg->y0 = begin->y;
	seg->x1 = end->x;
	seg->y1 = end->y;
}

void	bresenham(t_point begin, t_point end, t_img *img)
{
	t_bre	values;
	t_seg	seg;
	int		e2;

	init_seg_values(&seg, &begin, &end);
	init_bre_values(&values, &seg);
	while (1)
	{
		ft_put_pixel(&seg, img, img->basic_color);
		if (seg.x0 == seg.x1 && seg.y0 == seg.y1)
			break ;
		e2 = 2 * values.err;
		if (e2 >= values.dy)
		{
			values.err += values.dy;
			seg.x0 += values.sx;
		}
		if (e2 <= values.dx)
		{
			values.err += values.dx;
			seg.y0 += values.sy;
		}
	}
}
