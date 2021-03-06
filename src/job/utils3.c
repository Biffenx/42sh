/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:58:32 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:39:01 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	format_job_info(t_job *job, const char *status)
{
	if (g_debug)
		ft_dprintf(STDERR_FILENO, "%ld (%s): %s\n",
			(long)job->pgid, status, job->command);
}

static void	find_current(void)
{
	t_job	*job;

	job = g_shell->jobs;
	while (job)
	{
		if (job_is_stopped(job))
		{
			g_shell->current = job;
			return ;
		}
		job = job->next;
	}
	g_shell->current = g_shell->jobs;
}

void 	do_job_notification(void)
{
	t_job	*job;
	t_job	*jlast;
	t_job	*jnext;

	jlast = NULL;
	job = g_shell->jobs;
	while (job)
	{
		jnext = job->next;
		if (job_is_completed(job))
		{
			format_job_info(job, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				g_shell->jobs = jnext;
			free_job(job);
		}
		else if (job_is_stopped(job) && !job->notified)
		{
			format_job_info(job, "stopped");
			job->notified = 1;
			jlast = job;
		}
		else
			jlast = job;
		job = jnext;
	}
	if (!g_shell->current)
		find_current();
	update_status();
}

void 	mark_job_as_running(t_job *job)
{
	t_process	*process;

	process = job->first_process;
	while (process)
	{
		process->stopped = 0;
		process = process->next;
	}
	job->notified = 0;
}

void	continue_job(t_job *job, int foreground)
{
	mark_job_as_running(job);
	if (foreground)
		put_job_in_foreground(job, 1);
	else
		put_job_in_background(job, 1);
}
