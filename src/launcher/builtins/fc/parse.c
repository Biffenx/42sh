/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 09:28:11 by vkuokka           #+#    #+#             */
/*   Updated: 2021/04/25 10:42:40 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		parse_index(int nbr, int histsize)
{
	nbr < 0 ? nbr = histsize + nbr : 0;
	nbr > histsize ? nbr = histsize - 1 : 0;
	nbr < 0 ? nbr = 0 : 0;
	return (nbr);
}

int		find_index(char *str, int *options)
{
	int	i;

	if (ft_isdigit(str[0]) || (str[0] == '-' && ft_isdigit(str[1])))
		return (ft_atoi(str));
	i = ft_arrlen(g_shell->history, HISTORY_SIZE) - 2;
	i < 0 ? i = 0 : 0;
	while (g_shell->history[i])
	{
		if (ft_strstr(g_shell->history[i], str))
			return (i);
		i += 1;
	}
	ft_putstr_fd(FC_ERR_EVENT, STDERR_FILENO);
	*options |= 1 << 5;
	return (0);
}
