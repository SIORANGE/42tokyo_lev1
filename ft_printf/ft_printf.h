/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:39:03 by ktakesat          #+#    #+#             */
/*   Updated: 2020/12/30 03:20:25 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define ERR -1
# define FAILED 0
# define SMALL 0
# define SUCCESS 1
# define CAPITAL 1
# define ZERO 1
# define LEFT 2

typedef struct		s_flags
{
	int flg;
	int wid;
	int prec;
	int conv;
}					t_flags;

int					dig(long long num, unsigned int base);
int					ft_mini_atoi(char *str);
int					ft_strlen(const char *s);
void				super_converter(char **s, t_flags fmt);
void				remaker(char **s, unsigned long long up,\
													int start, t_flags fmt);

void				treat_base(long long num, int base, char *s, int conv);
void				insert_minus(char *s, int size);
char				*treat_prec_num(long long num, t_flags *fmt, int base);
char				*treat_wid(long long num, t_flags *fmt,\
												char *s, int b_index);
char				*ntoa_base(long long num, t_flags *fmt);

int					print_ux(t_flags *format, va_list args);
long long			print_s(t_flags *fmt, va_list args);
int					print_p(t_flags *fmt, va_list args);
int					print_cd(t_flags *format, va_list args);
int					print_percent(t_flags *fmt);

int					treat_fmt(t_flags *fmt, va_list args);
int					store_nums(char *string, va_list args,\
										int *wid_or_per, int *flg);
int					store_fmt(char *string, t_flags *fmt, va_list args);
int					ft_printf(const char *string, ...);

#endif
