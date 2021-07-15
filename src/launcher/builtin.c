/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:43:11 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 13:49:53 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int run_builtin(char **argv)
{
	if (ft_strequ(argv[0], "fc"))
		return (fc(argv));
	else if (ft_strequ(argv[0], "alias"))
		return (alias_builtin(argv));
	else if (ft_strequ(argv[0], "bg"))
		return (bg_builtin(argv + 1));
	else if (ft_strequ(argv[0], "cd"))
		return (cd_builtin(argv + 1));
	else if (ft_strequ(argv[0], "echo"))
		return (echo_builtin(argv));
	else if (ft_strequ(argv[0], "exit"))
		exit_builtin();
	else if (ft_strequ(argv[0], "export"))
		return (export_builtin(argv));
	else if (ft_strequ(argv[0], "fg"))
		return (fg_builtin(argv + 1));
	else if (ft_strequ(argv[0], "hash"))
		return (hash_builtin(argv));
	else if (ft_strequ(argv[0], "jobs"))
		return (jobs_builtin(argv + 1));
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
