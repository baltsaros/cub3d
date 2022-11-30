/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/30 11:39:21 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// find a wall texture
char	*find_param(char **raw, char *param, t_data *data)
{
	size_t	i;
	size_t	len;
	char	**tmp;
	char	*ret;

	i = 0;
	len = ft_strlen(param);
	while (raw[i] && ft_strncmp(raw[i], param, len))
		++i;
	if (!raw[i])
		return (NULL);
	if (i > data->j)
		data->j = i;
	tmp = ft_split(raw[i], ' ');
	alloc_check_big(tmp, data);
	ret = cub_strdup(tmp[1], data);
	cub_free(tmp);
	return (ret);
}

// find color setting for floor/ceiling
char	*find_param_color(char **raw, char *param, t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ret;

	j = 0;
	len = ft_strlen(param);
	while (raw[j] && ft_strncmp(raw[j], param, len))
		++j;
	if (!raw[j])
		return (NULL);
	if (j > data->j)
		data->j = j;
	i = 0;
	while (raw[j][i] && !ft_isdigit(raw[j][i]))
		++i;
	if (!raw[j][i])
		return (NULL);
	ret = cub_strdup(raw[j] + i, data);
	return (ret);
}

size_t	skip_wspace(char **map, size_t j, size_t i)
{
	while (map[j][i] && check_charset(map[j][i],
		" \f\n\r\t\v"))
		++i;
	return (i);
}
