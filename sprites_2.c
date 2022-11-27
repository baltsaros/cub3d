/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:31:38 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 23:24:20 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_depth(t_data *data)
{
	int	i;

	i = 0;
	data->depth = (int *) malloc (WIDTH * sizeof(int));
	if (!data->depth)
		return (ERROR_FAILED_M);
	while (i != WIDTH)
	{
		data->depth[i] = 0;
		i++;
	}
	data->is_depth_allocated = 1;
	return (EXIT_SUCCESS);
}