/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/17 18:10:01 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*cub_strjoin_free(char *rest, char *buf, t_data *data)
{
	char	*unis;
	size_t	i;
	size_t	j;

	if (!rest || !buf)
		return (0);
	data->j = ft_strlen(rest) + ft_strlen(buf) + 1;
	unis = cub_malloc(sizeof(*unis) * data->j, data);
	i = 0;
	while (rest[i])
	{
		unis[i] = rest[i];
		++i;
	}
	j = 0;
	while (buf[j])
	{
		unis[i + j] = buf[j];
		++j;
	}
	unis[j + i] = '\0';
	free(rest);
	return (unis);
}

char	*cub_charjoin_free(char *line, char b, t_data *data)
{
	size_t	i;
	char	*unis;

	i = 0;
	while (line[i])
		++i;
	unis = cub_malloc(sizeof(*unis) * (i + 2), data);
	i = 0;
	while (line[i])
	{
		unis[i] = line[i];
		++i;
	}
	unis[i] = b;
	unis[i + 1] = 0;
	free(line);
	return (unis);
}

char	*cub_strndup(char const *str, size_t size, t_data *data)
{
	char	*dest;
	size_t	i;

	dest = cub_malloc((sizeof(char) * (size + 1)), data);
	i = 0;
	while (str[i] && i < size)
	{
		dest[i] = str[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

void	*cub_malloc(size_t n, t_data *data)
{
	void	*ptr;

	(void)data;
	ptr = malloc(n);
	if (!ptr)
	{
		write(2, "Cub3d: ", 7);
		write(2, "allocation failed\n", 18);
		cub_free_all(data);
		exit(1);
	}
	return (ptr);
}

char	*cub_strdup(const char *s, t_data *data)
{
	char	*dest;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	dest = cub_malloc(sizeof(char) * (size + 1), data);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}
