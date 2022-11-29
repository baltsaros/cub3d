/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:05:24 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/29 15:08:04 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	quicksort_2(t_data *data, t_quicksort quick, int first, int last)
{
	quick.tmp = data->objs[quick.pivot];
	data->objs[quick.pivot] = data->objs[quick.j];
	data->objs[quick.j] = quick.tmp;
	quicksort(data, quick, first, quick.j - 1);
	quicksort(data, quick, quick.j + 1, last);
}

void	quicksort(t_data *data, t_quicksort quick, int first, int last)
{
	if (first < last)
	{
		quick.pivot = first;
		quick.i = first;
		quick.j = last;
		while (quick.i < quick.j)
		{
			while (data->objs[quick.i].distance
				<= data->objs[quick.pivot].distance
				&& quick.i < last)
				quick.i++;
			while (data->objs[quick.j].distance
				> data->objs[quick.pivot].distance)
				quick.j--;
			if (quick.i < quick.j)
			{
				quick.tmp = data->objs[quick.i];
				data->objs[quick.i] = data->objs[quick.j];
				data->objs[quick.j] = quick.tmp;
			}
		}
		quicksort_2(data, quick, first, last);
	}
}
