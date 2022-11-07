/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:04:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/07 17:39:20 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_xpm(char *str)
{
    int i;

    i = ft_strlen(str) - 1;
    if (str[i] != 'm' || str[i - 1] != 'p' || str[i - 2] != 'x' || str[i - 3] != '.')
        return (1);
    return (0);
}

int load_buf(t_text *text)
{
    char    *dst;
    int     i;
    int     x;
    int     y;

    i = 0;
    y = 0;
    text->buf = (int *) malloc (((text->height * text->width) + 1) * sizeof(int));
    if (!text->buf)
        return (1);
    while (y < text->height)
    {
        x = 0;
        while (x < text->width)
        {
            dst = text->img.addr + (y * text->img.line_length + x * (text->img.bpp / 8));
            text->buf[i] = *(unsigned int *)dst;
            x++;
            i++;
        }
        y++;
    }
    return (0);
}

int load_textures(t_data *data)
{
    if (is_xpm(data->map.no) || is_xpm(data->map.so) || is_xpm(data->map.ea) || is_xpm(data->map.we))
        return (1);
    data->no_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.no, &data->no_text.width, &data->no_text.height);
    data->so_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.so, &data->so_text.width, &data->so_text.height);
    data->ea_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.ea, &data->ea_text.width, &data->ea_text.height);
    data->we_text.img.img_ptr = mlx_xpm_file_to_image(data->mlx, data->map.we, &data->we_text.width, &data->we_text.height);
    if (!data->no_text.img.img_ptr || !data->so_text.img.img_ptr
        || !data->ea_text.img.img_ptr || !data->we_text.img.img_ptr)
        return (1);
    data->no_text.img.addr = mlx_get_data_addr(data->no_text.img.img_ptr, &data->no_text.img.bpp, &data->no_text.img.line_length, &data->no_text.img.endian);
    data->so_text.img.addr = mlx_get_data_addr(data->so_text.img.img_ptr, &data->so_text.img.bpp, &data->no_text.img.line_length, &data->no_text.img.endian);
    data->ea_text.img.addr = mlx_get_data_addr(data->ea_text.img.img_ptr, &data->ea_text.img.bpp, &data->no_text.img.line_length, &data->no_text.img.endian);
    data->we_text.img.addr = mlx_get_data_addr(data->we_text.img.img_ptr, &data->we_text.img.bpp, &data->no_text.img.line_length, &data->no_text.img.endian);
    if (load_buf(&data->no_text) || load_buf(&data->so_text)
        || load_buf(&data->ea_text) || load_buf(&data->we_text))
        return (1);
    return (0);
}