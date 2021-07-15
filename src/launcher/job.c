/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:22:21 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 09:47:06 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		wait_for_process(t_process *process)
{
	int			status;
	pid_t		pid;

	status = 0;
	pid = 0;
	while (!process->completed)
	{
		pid = waitpid(process->pid, &status, WUNTRACED);
		mark_process_status(pid, status);
	}
	ft_printf("process exit %i\n", process->exit);
	if (process->condition == 1 && process->exit == 0)
		return (0);
	else if (process->condition == 2 && process->exit != 0)
		return (0);
	else if (process->condition)
		return (1);
	return (0);
}

static int		resolve_launch(t_process *prev)
{
	if (!prev)
		return (0);
	else if (prev->condition)
		return (wait_for_process(prev));
	else
		return (0);
}
void			launch_job(t_job *job, int foreground)
{
	t_process	*process;
	t_process	*prev;
	pid_t		pid;
	int			mypipe[2];
	int			infile;
	int			outfile;

	job->launched = 1;
	if (!g_shell->current)
		g_shell->current = job;
	infile = job->stdin;
	process = job->first_process;
	prev = NULL;
	while (process)
	{
		if (process->next)
		{
			if (pipe(mypipe) < 0)
			{
				exit(1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = job->stdout;
		if (!resolve_launch(prev))
		{
			if (isbuiltin(process->argv[0]))
			{
					process->completed = 1;
					process->exit = run_builtin(process->argv);
			}
			else
			{
				pid = fork();
				if (pid == 0)
					launch_process(process, job, job->pgid, infile, outfile, job->stderr, foreground);
				else if (pid < 0)
					exit(1);
				else
				{
					process->pid = pid;
					if (g_shell->mode & INTERACTIVE)
					{
						if (!job->pgid)
							job->pgid = pid;
						setpgid(pid, job->pgid);
					}
				}
			}
		}
		else
		{
			process->completed = 1;
			process->exit = prev->exit;
		}
		if (infile != job->stdin)
			close(infile);
		if (outfile != job->stdout)
			close(outfile);
		infile = mypipe[0];
		prev = process;
		process = process->next;
	}
	format_job_info(job, "launched");
	if (~g_shell->mode & INTERACTIVE)
		wait_for_job(job);
	else if (foreground)
		put_job_in_foreground(job, 0);
	else
		put_job_in_background(job, 0);
}
