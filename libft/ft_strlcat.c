/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:33:36 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/14 10:07:53 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	remain;

	remain = size;
	while (*dst && remain > 0)
	{
		++dst;
		--remain;
	}
	len_d = size - remain;
	len_s = 0;
	while (src[len_s])
		++len_s;
	if (remain == 0)
		return (len_d + len_s);
	while (*src && remain > 1)
	{
		*dst = *src;
		++dst;
		++src;
		--remain;
	}
	*dst = '\0';
	return (len_d + len_s);
}
