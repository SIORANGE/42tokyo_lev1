/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:40:42 by ktakesat          #+#    #+#             */
/*   Updated: 2021/01/04 13:35:32 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			treat_fmt(t_flags *fmt, va_list args)
{
	if (fmt->conv == 's')
		return (print_s(fmt, args));
	if (fmt->conv == 'p')
		return (print_p(fmt, args));
	if (fmt->conv == 'c' || fmt->conv == 'd' || fmt->conv == 'i')
		return (print_cd(fmt, args));
	if (fmt->conv == 'x' || fmt->conv == 'X' || fmt->conv == 'u')
		return (print_ux(fmt, args));
	if (fmt->conv == '%')
		return (print_percent(fmt));
	return (ERR);
}

int			store_nums(char *string, va_list args, int *wid_or_per, int *flg)
{
	int res;

	res = 0;
	if (string[res] == '*')
	{
		*wid_or_per = va_arg(args, int);
		if (*wid_or_per < 0 && flg)
		{
			*flg = LEFT;
			*wid_or_per *= -1;
		}
		res++;
	}
	else if (string[res] >= '0' && string[res] <= '9')
	{
		*wid_or_per = ft_mini_atoi(&string[res]);
		res += dig(*wid_or_per, 10);
	}
	return (res);
}

int			store_format(char *string, t_flags *fmt, va_list args)
{
	int res;

	res = 1;
	while (string[res] == '-' || string[res] == '0')
		fmt->flg = (string[res++] == '0' && fmt->flg != LEFT) ? ZERO : LEFT;
	res += store_nums(&string[res], args, &(fmt->wid), &(fmt->flg));
	if ((fmt->wid <= INT_MIN + 1) || (fmt->wid >= INT_MAX))
		return (FAILED);
	if (string[res] == '.')
	{
		res++;
		while (string[res] == '0')
			res++;
		fmt->prec = 0;
		res += store_nums(&string[res], args, &(fmt->prec), 0);
		if (fmt->prec >= INT_MAX)
			return (FAILED);
		fmt->prec = (fmt->prec < 0) ? -1 : fmt->prec;
	}
	if (fmt->flg == ZERO && fmt->prec != -1 && string[res] != '%')
		fmt->flg = 0;
	fmt->conv = string[res++];
	return (res);
}

int			ft_printf(const char *string, ...)
{
	t_flags			format;
	va_list			args;
	int				check;
	int				res;

	res = 0;
	va_start(args, string);
	if (!string)
		return (FAILED);
	while (*string)
	{
		if (*string != '%')
			res += write(1, string++, 1);
		else
		{
			check = 0;
			format = (t_flags){.flg = 0, .wid = -1, .prec = -1, .conv = 0};
			if (!(check = store_format((char *)string, &format, args)))
				return (ERR);
			string += check;
			if ((res += treat_fmt(&format, args)) == -1)
				return (ERR);
		}
	}
	return (res);
}
