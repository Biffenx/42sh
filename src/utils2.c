/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:23:05 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/20 18:57:49 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** parse_index is useful tool for finding entires from history array.
*/

int	parse_index(int nbr, int histsize)
{
	nbr < 0 ? nbr = histsize + nbr : 0;
	nbr > histsize ? nbr = histsize - 1 : 0;
	nbr < 0 ? nbr = 0 : 0;
	return (nbr);
}
