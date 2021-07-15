/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:06:34 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 18:28:33 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/echo.1p.html
*/

int	echo_builtin(char **argv)
{
	int	i;

	i = 1;
	if (ft_strequ(argv[i], "-n"))
		i += 1;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i += 1;
	}
	if (!ft_strequ(argv[1], "-n"))
		write(1, "\n", 1);
	return (0);
}
