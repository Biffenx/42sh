/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:14:52 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/04 20:32:12 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Functions are not tested!!!

void			put_job_in_foreground(t_job *job, int cont)
{
	tcsetpgrp(STDIN_FILENO, job->pgid); // MAY CAUSE PROBLEMS!!!
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->tmodes); // PROBLEMS???
		if (kill(-job->pgid, SIGCONT) < 0)
			exit(1);
	}
	wait_for_job(job);
	tcsetpgrp(STDIN_FILENO, g_shell->pgid); // PROBLEMS???
	tcgetattr(STDIN_FILENO, &job->tmodes); // PROBLEMS???
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell->terminal.original); // PROBLEMS???
}

void			put_job_in_background(t_job *job, int cont)
{
	if (cont)
		if (kill (-job->pgid, SIGCONT) < 0)
			exit(1);
}

int				mark_process_status(pid_t pid, int status)
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
						process->stopped = 1;
					else
					{
						process->completed = 1;
						if (WIFSIGNALED(status))
							ft_dprintf(STDERR_FILENO, "%d: Terminated by signal %d.\n", \
									(int)pid, WTERMSIG(process->status));
					}
					return 0;
				}
				process = process->next;
			}
			job = job->next;
		}
		ft_dprintf(STDERR_FILENO, "No child process %d.\n", pid);
		return -1;
	}
	else
		return -1;
}

void			update_status(void)
{
	int			status;
	pid_t		pid;

	status = 0;
	pid = 0;
	while (!mark_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

void wait_for_job(t_job *job)
{
	int status;
	pid_t pid;

	status = 0;
	pid = 0;
	while (!mark_process_status(pid, status) && !job_is_stopped(job) && !job_is_completed(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}
