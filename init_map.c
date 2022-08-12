/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:13:40 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/16 12:09:55 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**init_empty_map(char **args_map, int row, int col)
{
	int	i;
	int	**map;

	i = 0;
	map = (int **) malloc (row * sizeof(int *));
	if (!map)
		free_strarray_error_and_exit(args_map, strerror(errno));
	while (i < row)
	{
		map[i] = (int *) malloc (col * sizeof(int));
		if (!map)
		{
			free_all_int_array(map, row);
			free_strarray_error_and_exit(args_map, strerror(errno));
		}
		i++;
	}
	return (map);
}

int	*init_line(char **tmp, int *line, int col)
{
	int	i;

	i = 0;
	while (tmp[i] && i < col)
	{
		line[i] = ft_atoi(tmp[i]);
		i++;
	}
	return (line);
}

int	**fill_map(char **args_map, int **map, int row, int col)
{
	int		i;
	char	**tmp;

	i = 0;
	while (args_map[i] && i < row)
	{
		tmp = ft_split(args_map[i], ' ');
		if (!tmp)
		{
			free_all_int_array(map, row);
			free_strarray_error_and_exit(args_map, strerror(errno));
		}
		map[i] = init_line(tmp, map[i], col);
		free_all_array(tmp);
		i++;
	}
	return (map);
}

t_map	init_map(char	*args)
{
	t_map	map;
	char	**args_map;

	args_map = get_args_map(args);
	map.row = get_row(args_map);
	map.col = get_col(args_map);
	map.map = init_empty_map(args_map, map.row, map.col);
	map.map = fill_map(args_map, map.map, map.row, map.col);
	free_all_array(args_map);
	return (map);
}
