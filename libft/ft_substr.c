/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:34:26 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/14 10:08:37 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_s;
	size_t	len_new;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	len_new = 0;
	while (s[start + len_new] && len > len_new)
		++len_new;
	substr = (char *)malloc(sizeof(*substr) * (len_new + 1));
	if (NULL == substr)
		return (0);
	if (len_s < start)
	{
		ft_memset(substr, 0, len_new + 1);
		return (substr);
	}
	ft_strlcpy(substr, s + start, len_new + 1);
	return (substr);
}
