/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:09:35 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/16 10:35:33 by vkuokka          ###   ########.fr       */
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
	set_file_descriptors(process, job, infile, outfile, errfile);
	execve(process->path, process->argv, environ);
	write(2, PROC_ERR_EXEC, ft_strlen(PROC_ERR_EXEC));
	exit(127);
}
