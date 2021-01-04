/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:12:06 by ktakesat          #+#    #+#             */
/*   Updated: 2020/12/30 02:50:41 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					print_ux(t_flags *format, va_list args)
{
	long long			ux;
	char				*s;
	int					res;

	ux = (long long)va_arg(args, unsigned int);
	if (!(s = ntoa_base(ux, format)))
		return (-1);
	res = (int)write(1, s, ft_strlen(s));
	free(s);
	return (res);
}

int					print_cd(t_flags *format, va_list args)
{
	long long			d;
	char				*s;
	int					res;
	int					count;
	char				c;

	d = (long long)va_arg(args, int);
	count = 0;
	res = 0;
	if (format->conv == 'c')
	{
		while (format->flg != LEFT && count++ < format->wid - 1)
			res += write(1, " ", 1);
		c = (char)d;
		res += write(1, &c, 1);
		while (format->flg == LEFT && res < format->wid)
			res += write(1, " ", 1);
		return (res);
	}
	s = ntoa_base(d, format);
	res += (int)write(1, s, ft_strlen(s));
	free(s);
	return (res);
}

long long			print_s(t_flags *fmt, va_list args)
{
	char	*s;
	int		len;
	int		count;

	count = 0;
	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	len = (int)ft_strlen(s);
	if (fmt->prec != -1)
		len = (fmt->prec < len) ? fmt->prec : len;
	if (fmt->flg == LEFT)
	{
		write(1, s, len);
		while (len < fmt->wid - count++)
			write(1, " ", 1);
	}
	else
	{
		while (len < fmt->wid - count++)
			write(1, (fmt->flg == ZERO) ? "0" : " ", 1);
		write(1, s, len);
	}
	return ((fmt->wid > len) ? fmt->wid : len);
}

int					print_percent(t_flags *fmt)
{
	int		count;
	int		res;

	count = 0;
	res = 0;
	if (fmt->flg == LEFT)
	{
		res += write(1, "%", 1);
		while (count++ < fmt->wid - 1)
			res += write(1, " ", 1);
	}
	else
	{
		while (count++ < fmt->wid - 1)
			res += write(1, (fmt->flg == ZERO) ? "0" : " ", 1);
		res += write(1, "%", 1);
	}
	return (res);
}

int					print_p(t_flags *fmt, va_list args)
{
	long long			p;
	char				*s;
	int					res;
	int					index;

	p = (long long)va_arg(args, void *);
	s = ntoa_base(p, fmt);
	index = -1;
	while (s[++index])
		if (s[index] == '-')
			super_converter(&s, *fmt);
	res = (int)write(1, s, ft_strlen(s));
	free(s);
	return (res);
}
