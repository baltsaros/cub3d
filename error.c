/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:50:25 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/26 00:59:28 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    check_errors(t_data *data, int ret)
{
    if (ret == ERROR_IMG_PTR)
    {
        write(2, "Cub3d: ", 7);
        write(2, "init img_ptr failed\n", 20);
    }
    else if (ret == ERROR_TEXT_PTR)
    {
        write(2, "Cub3d: ", 7);
        write(2, "load textures failed\n", 21);
    }
    else if (ret == ERROR_BAD_EXT)
    {
        write(2, "Cub3d: ", 7);
        write(2, "wrong texture extension\n", 24);
    }
    leave(data, EXIT_FAILURE);
}