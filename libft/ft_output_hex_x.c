/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_hex_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:15:04 by abuzdin           #+#    #+#             */
/*   Updated: 2022/04/04 13:24:04 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		++len;
	while (nbr)
	{
		nbr = nbr / 16;
		++len;
	}
	return (len);
}

static int	ft_decrease(int *width)
{
	if (*width > 0)
	{
		--(*width);
		return (1);
	}
	return (0);
}

static void	ft_putnbr_un(unsigned int nb, int *r)
{
	if (nb >= 16)
	{
		ft_putnbr_un(nb / 16, r);
		nb = nb % 16;
	}
	if (nb < 10)
		ft_putchar(nb + '0', r);
	else
		ft_putchar(nb + 55, r);
}

void	ft_output_hex_x(t_par *params, unsigned int nbr, int *r)
{
	int	len;

	len = ft_nbrlen(nbr);
	if (params->dot == 0 && nbr == 0)
		len = 0;
	params->dot -= len;
	params->width -= len;
	if (params->sharp && nbr)
		params->width -= 2;
	while (params->width > params->dot && !params->zero
		&& !params->minus && ft_decrease(&params->width))
		ft_putchar(' ', r);
	if (params->sharp && nbr)
		ft_putstr("0X", r);
	while ((params->zero && params->width > 0) || params->dot > 0)
	{
		ft_putchar('0', r);
		--params->width;
		--params->dot;
	}	
	if (len)
		ft_putnbr_un(nbr, r);
	while (params->minus && ft_decrease(&params->width))
		ft_putchar(' ', r);
}
