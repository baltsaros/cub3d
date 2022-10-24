/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:32:13 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/14 10:06:44 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_ch;
	char	*src_ch;
	size_t	i;

	if (dest == src)
		return (dest);
	dest_ch = (char *)dest;
	src_ch = (char *)src;
	i = 0;
	if (dest_ch > src_ch)
	{
		while (n > 0)
		{
			dest_ch[n - 1] = src_ch[n - 1];
			--n;
		}
		return (dest);
	}
	while (n > i)
	{
		dest_ch[i] = src_ch[i];
		++i;
	}
	return (dest);
}
