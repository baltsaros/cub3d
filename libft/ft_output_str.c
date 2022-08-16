/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:09:08 by abuzdin           #+#    #+#             */
/*   Updated: 2022/04/04 13:24:36 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_decrease(int *width)
{
	if (*width > 0)
	{
		--(*width);
		return (1);
	}
	return (0);
}

void	ft_output_str(t_par *params, char *str, int *r)
{
	if (!str)
	{
		ft_output_str(params, "(null)", r);
		return ;
	}
	if (params->dot >= 0 && params->width && params->width > params->dot)
		params->width -= params->dot;
	else if (params->dot >= 0 && params->width && params->width < params->dot)
			params->width = params->dot - params->width + 1;
	else
		params->width -= ft_strlen(str);
	while (params->zero && ft_decrease(&params->width))
		ft_putchar('0', r);
	while (!params->zero && !params->minus && ft_decrease(&params->width))
		ft_putchar(' ', r);
	while (*str != '\0')
	{
		if (params->dot >= 0 && !(ft_decrease(&params->dot)))
			break ;
		ft_putchar(*str, r);
		++str;
	}
	while (params->minus && ft_decrease(&params->width))
		ft_putchar(' ', r);
}
