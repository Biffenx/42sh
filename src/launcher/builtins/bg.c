/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:29:51 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/22 20:20:42 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/bg.1p.html
*/

static int	raise_current(void)
{
	t_job *job;

	job = g_shell->current;
	if (job)
	{
		ft_putendl(job->command);
		mark_job_as_running(job);
		put_job_in_background(job, 1);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, JOB_ERR_NOTFOUND, "bg", "current");
	return (1);
}

static int	raise_job(char *s)
{
	int	job_id;
	t_job *job;

	job_id = ft_atoi(s);
	job = g_shell->jobs;
	while (job)
	{
		if (job->id == job_id)
		{
			ft_putendl(job->command);
			mark_job_as_running(job);
			put_job_in_background(job, 1);
			return (0);
		}
		job = job->next;
	}
	ft_dprintf(STDERR_FILENO, JOB_ERR_NOTFOUND, "bg", s);
	return (1);
}

int	bg_builtin(char **argv)
{
	if (argv[0] && argv[1])
		ft_dprintf(STDERR_FILENO, STR_ARG_ERR, "bg");
	else if (!*argv)
		return (raise_current());
	else
		return (raise_job(*argv));
	return (1);
}
