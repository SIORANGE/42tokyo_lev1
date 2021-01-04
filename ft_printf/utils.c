/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 22:17:51 by ktakesat          #+#    #+#             */
/*   Updated: 2021/01/04 01:08:44 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_strlen(const char *s)
{
	int len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int					ft_mini_atoi(char *str)
{
	long long	i;
	long long	nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] != '\0' && str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && nbr <= INT_MAX)
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	nbr = ((nbr > INT_MAX) && sign > 0) ? INT_MAX : nbr;
	nbr = ((nbr > -INT_MIN) && sign < 0) ? -INT_MIN : nbr;
	if (sign == -1)
		return (-nbr);
	return (nbr);
}

int					dig(long long num, unsigned int base)
{
	int		dig;

	if (num == INT_MIN)
		return (10);
	dig = 0;
	if (num < 0)
		num *= -1;
	while (num /= base)
		dig++;
	dig++;
	return (dig);
}

void				remaker(char **s, unsigned long long up,\
												int start, t_flags fmt)
{
	char			temp[30];
	int				i;

	i = 0;
	while (up != 0)
	{
		if ((up % 16) < 10)
			temp[i++] = (up % 16) + 48;
		else
			temp[i++] = (up % 16) + 87;
		up /= 16;
	}
	while (i-- > 0)
	{
		(*s)[start] = temp[i];
		start++;
	}
	if (((*s)[start] > 47 && (*s)[start] < 58) ||\
								((*s)[start] > 96 && (*s)[start] < 103))
		(*s)[start] = (start < fmt.wid && fmt.flg == LEFT) ? ' ' : '\0';
}

void				super_converter(char **s, t_flags fmt)
{
	int					i;
	int					num_start;
	long long			p;

	i = 0;
	p = 0;
	while ((*s)[i] != '-')
		i++;
	num_start = i;
	i += 3;
	while (((*s)[i] > 47 && (*s)[i] < 58) || ((*s)[i] > 96 && (*s)[i] < 103))
	{
		p = (((*s)[i] >= '0' && (*s)[i] <= '9') ? -(long long)(*s)[i] + '0'\
									: -(long long)(*s)[i] + 'a' - 10) + 16 * p;
		i++;
	}
	if ((unsigned long long)(-p) > 10000000000000000000llu -\
			(unsigned long long)__LONG_LONG_MAX__\
				&& fmt.flg != LEFT && fmt.wid > dig(p, 16))
		(*s)[num_start++] = ' ';
	(*s)[num_start++] = '0';
	(*s)[num_start++] = 'x';
	remaker(s, (unsigned long long)p, num_start, fmt);
}
