/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:33:49 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/24 17:24:40 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s2;

	i = 0;
	if (!s || !f)
		return (NULL);
	s2 = (char *)malloc(sizeof(*s2) * (ft_strlen(s) + 1));
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = (*f)(i, s[i]);
		++i;
	}
	s2[i] = '\0';
	return (s2);
}
