/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:54:26 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/04 10:33:03 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_set_params(t_par *params)
{
	params->zero = 0;
	params->minus = 0;
	params->dot = -1;
	params->space = 0;
	params->plus = 0;
	params->sharp = 0;
	params->width = 0;
	params->type = 0;
}

static void	ft_check_params(const char **str, t_par *params)
{
	while (**str == '#' || **str == '+' || **str == '-' || **str == ' '
		|| **str == '0')
	{
		if (**str == '0' && !params->minus)
			params->zero = 1;
		else if (**str == ' ')
			params->space = 1;
		else if (**str == '+')
		{
			params->space = 0;
			params->plus = 1;
		}
		else if (**str == '-')
		{
			params->minus = 1;
			params->zero = 0;
		}
		else if (**str == '#')
			params->sharp = 1;
		++(*str);
	}
}

static void	ft_check_params_extra(const char **str, t_par *params)
{	
	while (ft_isdigit(**str))
	{
		params->width = params->width * 10 + **str - '0';
		++(*str);
	}	
	if (**str == '.')
	{
		params->zero = 0;
		params->dot = 0;
		++(*str);
		while (ft_isdigit(**str))
		{
			params->dot = params->dot * 10 + **str - '0';
			++(*str);
		}	
	}
	if (**str == 'd' || **str == 'i' || **str == 's' || **str == 'c'
		|| **str == 'x' || **str == 'X' || **str == 'u'
		|| **str == 'p' || **str == '%')
	{
		params->type = **str;
		++(*str);
	}
}

static void	ft_output(va_list arg, t_par *params, int *r)
{
	if (params->type == 'c')
		ft_output_char(params, va_arg(arg, unsigned int), r);
	else if (params->type == 's')
		ft_output_str(params, va_arg(arg, char *), r);
	else if (params->type == 'd' || params->type == 'i')
		ft_output_nbr(params, va_arg(arg, int), r);
	else if (params->type == 'u')
		ft_output_nbr_un(params, va_arg(arg, unsigned int), r);
	else if (params->type == 'x')
		ft_output_hex(params, va_arg(arg, unsigned int), r);
	else if (params->type == 'X')
		ft_output_hex_x(params, va_arg(arg, unsigned int), r);
	else if (params->type == 'p')
		ft_output_ptr(params, va_arg(arg, unsigned long long), r);
	else if (params->type == '%')
		ft_output_char(params, '%', r);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	t_par	params;
	int		r;

	va_start(arg, str);
	r = 0;
	while (*str)
	{
		if (*str == '%')
		{
			++str;
			ft_set_params(&params);
			ft_check_params(&str, &params);
			ft_check_params_extra(&str, &params);
			ft_output(arg, &params, &r);
		}
		else
		{
			ft_putchar(*str, &r);
			++str;
		}
	}
	va_end(arg);
	return (r);
}
