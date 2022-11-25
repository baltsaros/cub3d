/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_er.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:28:57 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/25 16:59:40 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi_er(const char *str, int *error)
{
	int		i;
	int		j;
	long	n;

	i = 0;
	n = 0;
	j = i;
	while (str[j])
	{
		if (str[j] < 48 || str[j] > 57)
			*error = 1;
		++j;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = n * 10 + str[i] - '0';
		++i;
		if (n > INT_MAX)
			*error = 1;
	}
	return (n);
}
