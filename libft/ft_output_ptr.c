/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:07:37 by abuzdin           #+#    #+#             */
/*   Updated: 2022/04/04 13:24:33 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(unsigned long long nbr)
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

static void	ft_putnbr_un(unsigned long long nb, int *r)
{
	if (nb >= 16)
	{
		ft_putnbr_un(nb / 16, r);
		nb = nb % 16;
	}
	if (nb < 10)
		ft_putchar(nb + '0', r);
	else
		ft_putchar(nb + 87, r);
}

void	ft_output_ptr(t_par *params, unsigned long long nbr, int *r)
{
	params->width = params->width - ft_nbrlen(nbr) - 2;
	while ((params->dot <= 0) && !params->zero && !params->minus
		&& ft_decrease(&params->width))
		ft_putchar(' ', r);
	ft_putstr("0x", r);
	while (params->zero && ft_decrease(&params->width))
		ft_putchar('0', r);
	params->dot -= ft_nbrlen(nbr);
	while (params->dot >= 0 && ft_decrease(&params->dot))
		ft_putchar('0', r);
	ft_putnbr_un(nbr, r);
	while (params->minus && (params->dot < 0) && ft_decrease(&params->width))
		ft_putchar(' ', r);
}
