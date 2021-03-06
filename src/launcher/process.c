/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:09:35 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/06 14:17:59 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		launch_process(t_process *process, pid_t pgid, int infile, int outfile, int errfile, int foreground)
{
	pid_t	pid;

	if (g_shell->mode & INTERACTIVE)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		/* if (foreground)
			tcsetpgrp(STDIN_FILENO, pgid); // MAY CAUSE PROBLEMS!!! */
		foreground = foreground;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
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
	execve(ft_strjoin("/bin/", process->argv[0]), process->argv, g_shell->env); // BINARY PATH HAS TO BE LOCATED!!!
	write(2, "Process launch failed\n", 23);
	exit (1);
}
