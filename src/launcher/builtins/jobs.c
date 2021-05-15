/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:52:54 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/15 15:25:30 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/jobs.1p.html
*/

static char	*state(t_job *job)
{
	if (job_is_completed(job))
		return ("Completed");
	else if (job_is_stopped(job))
		return ("Stopped");
	else
		return ("Running");
}

int jobs_builtin(char **argv)
{
	t_job	*job;
	size_t	i;

	job = g_shell->jobs;
	i = 1;
	while (job)
	{
		if (ft_strequ(argv[1], "-l"))
			ft_printf("[%i] %i %s %s\n", i, job->pgid, state(job), job->command);
		else if (ft_strequ(argv[1], "-p"))
			ft_printf("%i\n", job->pgid);
		else
			ft_printf("[%i] %s %s\n", i, state(job), job->command);
		job = job->next;
		i += 1;
	}
	return (0);
}
