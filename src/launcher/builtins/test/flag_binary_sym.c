/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_binary_sym.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:48:05 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/05/16 21:48:21 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	flag_sym_eq_test(char *left, char *right, int *result)
{
	if (ft_strequ(left, right))
		*result = 0;
	else
		*result = 1;
	return (0);
}

int	flag_sym_noteq_test(char *left, char *right, int *result)
{
	if (!ft_strequ(left, right))
		*result = 0;
	else
		*result = 1;
	return (0);
}
