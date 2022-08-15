/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:34:23 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/24 17:21:16 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_set(int ch, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (1);
		++i;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tr;
	int		i;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = 0;
	while (check_set(s1[start], set))
		++start;
	i = ft_strlen(s1) - 1;
	while (i >= 0 && check_set(s1[i], set))
		--i;
	end = i + 1;
	if (start >= end)
		end = start;
	tr = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (NULL == tr)
		return (NULL);
	if (start < end)
		ft_memcpy(tr, s1 + start, (end - start));
	tr[end - start] = '\0';
	return (tr);
}
