/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/16 16:31:48 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_mlx_and_window(t_data *data)
{
    data->mlx = mlx_init();
    check_mlx(data->mlx, data);
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    check_win(data);
}

void    init_background(t_data *data)
{
    char **cell = ft_split(data->map.c, ',');
    int i;
    int j;
    int color;

    i = 0;
    color = create_trgb(0, ft_atoi(cell[0]), ft_atoi(cell[1]), ft_atoi(cell[2]));
    data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
    while (i != HEIGHT)
    {
        j = 0;
        while (j != WIDTH)
        {
            my_mlx_pixel_put(&data->img, j, i, color);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

int launcher(t_data *data)
{
    init_mlx_and_window(data);
    init_background(data);
    for(int i = 0; data->map.map[i]; i++)
        printf("%s\n", data->map.map[i]);

    // // Floor
    // char **floor = ft_split(data->map.f, ',');
    // data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    // data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
	// 		&data->img.line_length, &data->img.endian);
	// my_mlx_pixel_put(&data->img, 0, 0, create_trgb(0, ft_atoi(floor[0]), ft_atoi(floor[1]), ft_atoi(floor[2])));
    // mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 20, 20);

    mlx_key_hook(data->win, key_hook, &data);
	mlx_mouse_hook(data->win, mouse_hook, &data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, &data);
    mlx_loop(data->mlx);
    return (0);
}