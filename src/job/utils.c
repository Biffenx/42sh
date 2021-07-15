/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:58:14 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:44:46 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job	*find_job (pid_t pgid)
{
	t_job		*job;

	job = g_shell->jobs;
	while (job)
	{
		if (job->pgid == pgid)
			return (job);
		job = job->next;
	}
	return (NULL);
}

int	job_is_stopped (t_job *job)
{
	t_process	*process;

	process = job->first_process;
	while (process)
	{
		if (!process->completed && process->stopped)
			return (1);
		process = process->next;
	}
	return (0);
}

int	job_is_completed(t_job *job)
{
	t_process	*process;

	process = job->first_process;
	while (process)
	{
		if (!process->completed)
			return (0);
		g_shell->exit = process->exit;
		process = process->next;
	}
	return (1);
}
