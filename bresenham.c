/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:47:55 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/16 13:24:37 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	mlx_pixel_put_img(t_img	*img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

// void	init_bre_values(t_bre	*values, t_env	fdf)
// {
// 	values->dx = abs (fdf.x1 - fdf.x0);
// 	if (fdf.x0 < fdf.x1)
// 		values->sx = 1;
// 	else
// 		values->sx = -1;
// 	values->dy = -abs (fdf.y1 - fdf.y0);
// 	if (fdf.y0 < fdf.y1)
// 		values->sy = 1;
// 	else
// 		values->sy = -1;
// 	values->err = values->dx + values->dy;
// }

// void	ft_put_pixel(t_env	fdf)
// {
// 	if ((fdf.x0 < fdf.win_size.x && fdf.y0 < fdf.win_size.y)
// 		&& (fdf.x0 >= 0 && fdf.y0 >= 0))
// 		mlx_pixel_put_img(&fdf.img, fdf.x0, fdf.y0, 0xFFFFFF);
// }

// void	bresenham(t_env	fdf, t_point begin, t_point end)
// {
// 	t_bre	values;
// 	int		e2;

// 	fdf.x0 = begin.x;
// 	fdf.y0 = begin.y - begin.z;
// 	fdf.x1 = end.x;
// 	fdf.y1 = end.y - end.z;
// 	init_bre_values(&values, fdf);
// 	while (1)
// 	{
// 		ft_put_pixel(fdf);
// 		if (fdf.x0 == fdf.x1 && fdf.y0 == fdf.y1)
// 			break ;
// 		e2 = 2 * values.err;
// 		if (e2 >= values.dy)
// 		{
// 			values.err += values.dy;
// 			fdf.x0 += values.sx;
// 		}
// 		if (e2 <= values.dx)
// 		{
// 			values.err += values.dx;
// 			fdf.y0 += values.sy;
// 		}
// 	}
// }
