/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:57:45 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/24 07:58:39 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// copy str with a certain offset
char	*memcpy_offset(void *dest, const void *src, size_t n, size_t offset)
{
	size_t	i;
	char	*src_ch;
	char	*dest_ch;

	if (dest == src)
		return (dest);
	src_ch = (char *)src;
	dest_ch = (char *)dest;
	if (!dest || !src)
		return (0);
	i = 0;
	while (n > i)
	{
		dest_ch[i + offset] = src_ch[i];
		++i;
	}
	return (dest);
}

