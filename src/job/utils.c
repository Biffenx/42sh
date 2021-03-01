/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:58:14 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/01 11:55:11 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Functions are not tested!!!

t_job			*find_job (pid_t pgid)
{
	t_job		*job;

	job = g_shell->jobs;
	while (job)
	{
		if (job->pgid == pgid)
			return (job);
		job = job->next;
	}
	return NULL;
}

int				job_is_stopped (t_job *job)
{
	t_process	*process;

	process = job->first_process;
	while (process)
	{
		if (!process->completed && process->stopped)
			return (0);
		process = process->next;
	}
	return 1;
}

int				job_is_completed(t_job *job)
{
	t_process	*process;

	process = job->first_process;
	while (process)
	{
		if (!process->completed)
			return (0);
		process = process->next;
	}
	return 1;
}
