/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_binary_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:15:17 by jwilen            #+#    #+#             */
/*   Updated: 2021/05/16 22:01:44 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	flag_gt_test(char *r, char *l, int *res)
{
	long long	vl;
	long long	vr;

	if (check_longlong(l, &vl))
		return (2);
	if (check_longlong(r, &vr))
		return (2);
	if (vl < vr)
		*res = 0;
	else
		*res = 1;
	return (0);
}

static int	error_too_long(char *str)
{
	ft_printf("42sh: test: integer expression expected: %s\n", str);
	return (2);
}

static long long	ft_atoll_test(char *str, long long *value)
{
	char					*s;
	unsigned long long int	i;
	int						neg;
	unsigned long long int	rep;

	s = (char *)str;
	i = 0;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == '\r' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == ' ')
		i++;
	neg = 1;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			neg = -1;
	rep = 0;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
	{
		if ((neg == 1 && 10 * rep + (s[i] - '0') > 9223372036854775807)
			|| (neg == -1
				&& (10 * rep + (s[i] - '0') - 1) > 9223372036854775807))
			return (2);
		rep = 10 * rep + (s[i++] - '0');
	}
	*value = (long long)rep * (long long)neg;
	return (0);
}

static int	check_char_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && !ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_longlong(char *str, long long *value)
{
	*value = 0;
	if (check_char_number(str) || ft_atoll_test(str, value))
		return (error_too_long(str));
	return (0);
}
