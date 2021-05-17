/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 20:52:35 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/17 09:59:57 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/unset.1p.html
*/

int	unset_builtin(char **argv)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (argv[i])
	{
		err += unsetenv(argv[i]);
		err += hash_delete(g_shell->vars, argv[i]);
		i += 1;
	}
	g_shell->env = environ;
	return (err);
}
