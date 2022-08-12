/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:34:21 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/16 11:44:43 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_row(char	**args_map)
{
	int	i;

	i = 0;
	while (args_map[i])
		i++;
	return (i);
}

int	get_col(char	**args_map)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(args_map[0], ' ');
	if (!tmp)
		free_strarray_error_and_exit(args_map, strerror(errno));
	while (tmp[i])
		i++;
	free_all_array(tmp);
	return (i);
}
