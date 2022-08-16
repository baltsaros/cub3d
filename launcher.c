/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/16 17:04:51 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_mlx_and_window(t_data *data)
{
    data->mlx = mlx_init();
    check_mlx(data->mlx, data);
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    check_win(data);
    data->pos_x = 20;
    data->pos_y = 20;
}

void    fill_all_img(t_data *data, int color, int i_end, int j_end)
{
    int i;
    int j;

    i = 0;
    while (i != i_end)
    {
        j = 0;
        while (j != j_end)
        {
            printf("salut: %d\n", j);
            my_mlx_pixel_put(&data->img, j, i, color);
            j++;
        }
        i++;
    }
}

void    init_background(t_data *data)
{
    char **cell = ft_split(data->map.c, ',');
    int color;
    int i;
    int j;
    
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

void    draw_player(t_data *data, int pos_x, int pos_y)
{
    t_img   img;
    int     i;
    int     j;

    i = 0;
    img.img_ptr = mlx_new_image(data->mlx, 10, 10);
    img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.line_length, &img.endian);
    while (i != 10)
    {
        j = 0;
        while (j != 10)
        {
            my_mlx_pixel_put(&img, j, i, 0x000000);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, img.img_ptr, pos_x, pos_y);
}

void    draw_all(t_data *data)
{
    while (1)
        draw_player(data, data->pos_x, data->pos_y);
}

int launcher(t_data *data)
{
    init_mlx_and_window(data);
    init_background(data);
    draw_all(data);
    // for(int i = 0; data->map.map[i]; i++)
    //     printf("%s\n", data->map.map[i]);

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