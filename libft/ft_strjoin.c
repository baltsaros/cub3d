/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:33:32 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/14 10:07:48 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*unis;
	size_t	i;
	size_t	j;
	size_t	l;

	if (!s1 || !s2)
		return (0);
	l = ft_strlen(s1) + ft_strlen(s2);
	unis = (char *)malloc(sizeof(*unis) * (l + 1));
	if (NULL == unis)
		return (0);
	i = 0;
	while (s1[i])
	{
		unis[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		unis[i + j] = s2[j];
		++j;
	}
	unis[j + i] = '\0';
	return (unis);
}
