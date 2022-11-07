/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:04:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/07 14:36:46 by mthiry           ###   ########.fr       */
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
    return (0);
}