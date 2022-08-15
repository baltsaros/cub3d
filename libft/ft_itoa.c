/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:30:34 by abuzdin           #+#    #+#             */
/*   Updated: 2022/01/14 10:05:25 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	unsigned int	i;

	i = 0;
	if (n <= 0)
		++i;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_addnbr(int n, char *s, int i)
{
	unsigned int	nbr;

	if (n < 0)
	{
		nbr = -n;
		s[0] = '-';
	}
	else
		nbr = n;
	if (nbr >= 10)
	{
		ft_addnbr(nbr / 10, s, i - 1);
		nbr = nbr % 10;
	}
	if (nbr < 10)
	{
		s[i - 1] = nbr + '0';
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s_int;
	size_t	i;

	i = ft_intlen(n);
	s_int = (char *)malloc(sizeof(*s_int) * (i + 1));
	if (NULL == s_int)
		return (NULL);
	ft_addnbr(n, s_int, i);
	s_int[i] = '\0';
	return (s_int);
}
