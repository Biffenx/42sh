/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 07:36:50 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/17 18:54:24 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/fg.1p.html
*/

int	fg_builtin(char **argv)
{
	if (!argv)
		return (0);
	else
		return (1);
}
