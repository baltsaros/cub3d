/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:31:25 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/14 10:06:28 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	x;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	x = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == x)
			return ((void *)s + i);
		++i;
	}
	return (NULL);
}
