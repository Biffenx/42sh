/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:33:48 by jwilen            #+#    #+#             */
/*   Updated: 2021/05/17 23:36:46 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	count_argc(char **new_argv)
{
	int		i;

	i = 0;
	while (new_argv[i])
		i++;
	return (i);
}

int	check_errors(char **argv, int argc)
{
	int		ret;

	ret = 0;
	if (argc > 4)
	{
		ft_printf("42sh: test: too many arguments\n");
		ret = 2;
	}
	else if (argc == 3 && get_unary_option(argv[1]) == -1)
	{
		ft_printf("42sh: test: %s: unary operation expected\n", argv[1]);
		ret = 2;
	}
	else if (argc == 4 && get_binary_option(argv[2]) == -1)
	{
		ft_printf("42sh: test: %s: unary operation expected\n", argv[2]);
		ret = 2;
	}
	return (ret);
}

int	get_binary_option(char *argv)
{
	if (!ft_strcmp(argv, "="))
		return (op_sym_eq);
	else if (!ft_strcmp(argv, "!="))
		return (op_sym_noteq);
	else if (!ft_strcmp(argv, "-eq"))
		return (op_eq);
	else if (!ft_strcmp(argv, "-ne"))
		return (op_ne);
	else if (!ft_strcmp(argv, "-ge"))
		return (op_ge);
	else if (!ft_strcmp(argv, "-gt"))
		return (op_gt);
	else if (!ft_strcmp(argv, "-lt"))
		return (op_lt);
	else if (!ft_strcmp(argv, "-le"))
		return (op_le);
	return (-1);
}

static int	get_unary_option_alfa(char *argv)
{
	if (!ft_strcmp(argv, "-p"))
		return (flag_p);
	if (!ft_strcmp(argv, "-r"))
		return (flag_r);
	if (!ft_strcmp(argv, "-s"))
		return (flag_s);
	if (!ft_strcmp(argv, "-S"))
		return (flag_cap_s);
	if (!ft_strcmp(argv, "-u"))
		return (flag_u);
	if (!ft_strcmp(argv, "-w"))
		return (flag_w);
	if (!ft_strcmp(argv, "-x"))
		return (flag_x);
	if (!ft_strcmp(argv, "-z"))
		return (flag_z);
	return (-1);
}

int	get_unary_option(char *argv)
{
	if (!ft_strcmp(argv, "-b"))
		return (flag_b);
	if (!ft_strcmp(argv, "-c"))
		return (flag_c);
	if (!ft_strcmp(argv, "-d"))
		return (flag_d);
	if (!ft_strcmp(argv, "-e"))
		return (flag_e);
	if (!ft_strcmp(argv, "-f"))
		return (flag_f);
	if (!ft_strcmp(argv, "-g"))
		return (flag_g);
	if (!ft_strcmp(argv, "-L"))
		return (flag_cap_l);
	return (get_unary_option_alfa(argv));
}
