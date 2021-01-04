/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_converter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 05:15:12 by ktakesat          #+#    #+#             */
/*   Updated: 2020/12/30 00:07:16 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		treat_base(long long num, int base, char *s, int conv)
{
	int		size;

	size = dig(num, base);
	if (num < 0)
		num *= -1;
	if ((num % base) < 10)
		s[size - 1] = (num % base) + 48;
	else
		s[size - 1] = (num % base) + ((conv == 'X') ? 55 : 87);
	num /= base;
	size--;
	while (num != 0)
	{
		if ((num % base) < 10)
			s[size - 1] = (num % base) + 48;
		else
			s[size - 1] = (num % base) + ((conv == 'X') ? 55 : 87);
		num /= base;
		size--;
	}
}

void		insert_minus(char *s, int size)
{
	int		index;
	char	temp1;
	char	temp2;

	index = 0;
	while (!(s[index] >= '0' && s[index] <= '9'))
		index++;
	temp1 = s[index];
	s[index] = '-';
	index++;
	while (index < size + 1)
	{
		temp2 = s[index];
		s[index] = temp1;
		temp1 = temp2;
		index++;
	}
}

char		*treat_prec_num(long long num, t_flags *fmt, int base)
{
	char	*res;
	int		size;
	int		index;

	index = 0;
	size = dig(num, base);
	size = (fmt->prec > size) ? fmt->prec : size;
	size += (fmt->conv == 'p') ? 2 : 0;
	if (fmt->prec == 0 && num == 0)
		size = (fmt->conv == 'p') ? 2 : 0;
	if (!(res = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (fmt->conv == 'p')
	{
		res[index++] = '0';
		res[index++] = 'x';
	}
	while (dig(num, base) + index < size)
		res[index++] = '0';
	if (size != ((fmt->conv == 'p') ? 2 : 0))
		treat_base(num, base, &res[index], fmt->conv);
	res[size] = '\0';
	return (res);
}

char		*treat_wid(long long num, t_flags *fmt, char *s, int b_index)
{
	int					index;
	int					f_index;
	int					base;
	char				*temp;

	index = 0;
	f_index = 0;
	base = (fmt->conv == 'x' || fmt->conv == 'X' || fmt->conv == 'p') ? 16 : 10;
	s[b_index--] = '\0';
	if (!(temp = treat_prec_num(num, fmt, base)))
		return (NULL);
	while (index++ < fmt->wid - ((num < 0) ? 1 : 0) - ft_strlen(temp))
		if (fmt->flg == LEFT)
			s[b_index--] = (fmt->flg == ZERO && fmt->prec == -1) ? '0' : ' ';
		else
			s[f_index++] = (fmt->flg == ZERO && fmt->prec == -1) ? '0' : ' ';
	index = 0;
	while (index < ft_strlen(temp))
		s[f_index++] = temp[index++];
	free(temp);
	if (num < 0)
		insert_minus(s, f_index);
	return (s);
}

char		*ntoa_base(long long num, t_flags *fmt)
{
	char				*res;
	long long			temp;
	int					size;
	int					base;

	res = 0;
	base = (fmt->conv == 'x' || fmt->conv == 'X' || fmt->conv == 'p') ? 16 : 10;
	temp = num;
	if (temp < 0)
		temp *= -1;
	size = dig(num, base);
	size = (fmt->prec > size) ? fmt->prec : size;
	if (num < 0)
		size++;
	size += (fmt->conv == 'p') ? 2 : 0;
	if (fmt->prec == 0 && num == 0)
		size = (fmt->conv == 'p') ? 2 : 0;
	size = (fmt->wid > size) ? fmt->wid : size;
	if (!(res = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	res = treat_wid(num, fmt, res, size);
	return (res);
}
