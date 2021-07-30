/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:43:11 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 13:21:40 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int choose_builtin(char **argv)
{
	if (ft_strequ(argv[0], "fc"))
		return (fc(argv + 1));
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
		return (export_builtin(argv + 1));
	else if (ft_strequ(argv[0], "fg"))
		return (fg_builtin(argv + 1));
	else if (ft_strequ(argv[0], "hash"))
		return (hash_builtin(argv + 1));
	else if (ft_strequ(argv[0], "map"))
		return (map_builtin(argv));
	else if (ft_strequ(argv[0], "jobs"))
		return (jobs_builtin(argv + 1));
	else if (ft_strequ(argv[0], "set"))
		return (set_builtin(argv));
	else if (ft_strequ(argv[0], "test"))
		return (test_builtin(argv));
	else if (ft_strequ(argv[0], "type"))
		return (type_builtin(argv));
	else if (ft_strequ(argv[0], "unalias"))
		return (unalias_builtin(argv + 1));
	else if (ft_strequ(argv[0], "unset"))
		return (unset_builtin(argv));
	return (1);
}

int	run_builtin(char **argv, t_process *process, t_job *job, int infile, int outfile, int errfile)
{
	int in;
	int out;
	int err;
	int exit;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	err = dup (STDERR_FILENO);
	set_file_descriptors(process, job, infile, outfile, errfile);
	exit = choose_builtin(argv);
	reset_file_descriptors(in, out, err);
	return (exit);
}
