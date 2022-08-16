/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:29:45 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/16 11:52:28 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// allocation check for ft functions from libft
void	alloc_check_big(char **str, t_data *data)
{
	if (!str)
	{
		write(2, "Cub3d: ", 7);
		write(2, "allocation failed\n", 18);
		exit(1);
	}
}

void	alloc_check_small(void *str, t_data *data)
{
	if (!str)
	{
		write(2, "Cub3d: ", 7);
		write(2, "allocation failed\n", 18);
		exit(1);
	}
}
