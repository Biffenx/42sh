/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:09:35 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 18:31:52 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	launch_process(t_process *process, t_job *job,
		pid_t pgid, int infile, int outfile, int errfile, int foreground)
{
	pid_t	pid;

	if (g_shell->mode & INTERACTIVE)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(STDIN_FILENO, pgid);
		set_signals_default();
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	if (process->re_ag)
		parse_redir_aggre_list(process->re_ag, job, &outfile);
	execve(process->path, process->argv, environ);
	write(2, PROC_ERR_EXEC, ft_strlen(PROC_ERR_EXEC));
	exit(127);
}
