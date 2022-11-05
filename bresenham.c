/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:47:55 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/29 16:39:00 by mthiry           ###   ########.fr       */
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
	values->dx = abs (seg->p1.x - seg->p0.x);
	if (seg->p0.x < seg->p1.x)
		values->sx = 1;
	else
		values->sx = -1;
	values->dy = -abs (seg->p1.y - seg->p0.y);
	if (seg->p0.y < seg->p1.y)
		values->sy = 1;
	else
		values->sy = -1;
	values->err = values->dx + values->dy;
}

void	ft_put_pixel(t_data *data, t_seg *seg, t_img *img, int color)
{
	(void)data;
	if ((seg->p0.x < WIDTH && seg->p0.y < HEIGHT)
		&& (seg->p0.x >= 0 && seg->p0.y >= 0))
	{
		// if ((seg->p0.x < (int)(data->map.width * SQUARE_SIZE) && seg->p0.y < (int)(data->map.height * SQUARE_SIZE)))
		// {
			// if ((seg->p0.x >= 0) && (seg->p0.y >= 0))
				mlx_pixel_put_img(img, seg->p0.x, seg->p0.y, color);
		// }
	}
}

void	init_seg_values(t_seg *seg, t_point *begin, t_point *end)
{
	seg->p0.x = begin->x;
	seg->p0.y = begin->y;
	seg->p1.x = end->x;
	seg->p1.y = end->y;
}

void	bresenham(t_data *data, t_point begin, t_point end, t_img *img)
{
	t_bre	values;
	t_seg	seg;
	int		e2;

	init_seg_values(&seg, &begin, &end);
	init_bre_values(&values, &seg);
	while (1)
	{
		ft_put_pixel(data, &seg, img, img->basic_color);
		if (seg.p0.x == seg.p1.x && seg.p0.y == seg.p1.y)
			break ;
		e2 = 2 * values.err;
		if (e2 >= values.dy)
		{
			values.err += values.dy;
			seg.p0.x += values.sx;
		}
		if (e2 <= values.dx)
		{
			values.err += values.dx;
			seg.p0.y += values.sy;
		}
	}
}
