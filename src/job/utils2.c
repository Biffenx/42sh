/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:14:52 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:44:11 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	put_job_in_foreground(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->tmodes);
		if (kill(-job->pgid, SIGCONT) < 0)
			exit(1);
	}
	wait_for_job(job);
	tcsetpgrp(STDIN_FILENO, g_shell->pgid);
	tcgetattr(STDIN_FILENO, &job->tmodes);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell->terminal.original);
}

void	put_job_in_background(t_job *job, int cont)
{
	if (cont)
		if (kill(-job->pgid, SIGCONT) < 0)
			exit(1);
}

int	mark_process_status(pid_t pid, int status)
{
	t_job		*job;
	t_process	*process;

	job = g_shell->jobs;
	if (pid > 0)
	{
		while (job)
		{
			process = job->first_process;
			while (process)
			{
				if (process->pid == pid)
				{
					process->status = status;
					if (WIFSTOPPED(status))
					{
						process->stopped = 1;
						g_shell->current = job;
					}
					else
					{
						process->completed = 1;
						process->exit = WEXITSTATUS(status);
						if (WIFSIGNALED(status) && g_debug)
							ft_dprintf(STDERR_FILENO, "%d: Terminated by signal \
							%d.\n", (int)pid, WTERMSIG(process->status));
					}
					return (0);
				}
				process = process->next;
			}
			job = job->next;
		}
		ft_dprintf(STDERR_FILENO, "No child process %d.\n", pid);
		return (-1);
	}
	else
		return (-1);
}

void	update_status(void)
{
	int			status;
	pid_t		pid;

	status = 0;
	pid = 0;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	mark_process_status(pid, status);
}

void	wait_for_job(t_job *job)
{
	int			status;
	pid_t		pid;
	t_process	*process;

	status = 0;
	pid = 0;
	process = job->first_process;
	while (process)
	{
		if (process->pid)
		{
			pid = waitpid(process->pid, &status, WUNTRACED);
			mark_process_status(pid, status);
		}
		process = process->next;
	}
}
