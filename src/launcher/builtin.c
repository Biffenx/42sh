/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:43:11 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/16 21:11:24 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int run_builtin(char **argv)
{
	if (ft_strequ(argv[0], "fc"))
		return (fc(argv));
	else if (ft_strequ(argv[0], "alias"))
		return (alias_builtin(argv));
	else if (ft_strequ(argv[0], "cd"))
		return (cd_builtin(argv));
	else if (ft_strequ(argv[0], "echo"))
		return (echo_builtin(argv));
	else if (ft_strequ(argv[0], "exit"))
		exit_builtin();
	else if (ft_strequ(argv[0], "export"))
		return (export_builtin(argv));
	else if (ft_strequ(argv[0], "hash"))
		return (hash_builtin(argv));
	else if (ft_strequ(argv[0], "jobs"))
		return (jobs_builtin(argv));
	else if(ft_strequ(argv[0], "set"))
		return (set_builtin(argv));
	else if (ft_strequ(argv[0], "test"))
		return (test_builtin(argv));
	else if (ft_strequ(argv[0], "type"))
		return (type_builtin(argv));
	else if (ft_strequ(argv[0], "unalias"))
		return (unalias_builtin(argv));
	else if (ft_strequ(argv[0], "unset"))
		return (unset_builtin(argv));
	return (1);
}
