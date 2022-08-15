/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:58:26 by abuzdin           #+#    #+#             */
/*   Updated: 2022/04/04 13:24:27 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		++len;
	while (nbr)
	{
		nbr = nbr / 10;
		++len;
	}
	return (len);
}

static int	ft_dec(int *width)
{
	if (*width > 0)
	{
		--(*width);
		return (1);
	}
	return (0);
}

static void	ft_putnbr(int nbr, int *r)
{
	unsigned int	nb;

	if (nbr < 0)
		nb = -nbr;
	else
		nb = nbr;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, r);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar(nb + '0', r);
}

static void	ft_putsign(t_par *params, int nbr, int *r)
{
	if (params->space && (!params->plus) && params->width <= 0 && nbr >= 0)
		ft_putchar(' ', r);
	while (params->width > params->dot && !params->zero
		&& !params->minus && ft_dec(&params->width))
		ft_putchar(' ', r);
	if (params->plus && nbr >= 0)
		ft_putchar('+', r);
	if (nbr < 0)
		ft_putchar('-', r);
}

void	ft_output_nbr(t_par *params, int nbr, int *r)
{
	int	len;

	len = ft_nbrlen(nbr);
	if (params->dot == 0 && nbr == 0)
		len = 0;
	if (nbr < 0 && params->dot > 0)
		++params->dot;
	params->width -= len;
	params->dot -= len;
	if (params->plus && nbr >= 0)
		--params->width;
	ft_putsign(params, nbr, r);
	while ((params->zero && params->width > 0) || params->dot > 0)
	{
		ft_putchar('0', r);
		--params->width;
		--params->dot;
	}	
	if (len)
		ft_putnbr(nbr, r);
	while (params->minus && (params->dot <= 0) && ft_dec(&params->width))
		ft_putchar(' ', r);
}
