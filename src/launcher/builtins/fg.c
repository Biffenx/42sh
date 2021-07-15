/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 07:36:50 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 18:27:47 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/fg.1p.html
*/

static int	raise_current(void)
{
	t_job	*job;

	job = g_shell->current;
	if (job)
	{
		g_shell->current = job;
		ft_putendl(job->command);
		continue_job(job, 1);
		return (0);
	}
	ft_dprintf(STDERR_FILENO, JOB_ERR_NOTFOUND, "fg", "current");
	return (1);
}

static int	raise_job(char *s)
{
	int		job_id;
	t_job	*job;

	job_id = ft_atoi(s);
	job = g_shell->jobs;
	while (job)
	{
		if (job->id == job_id)
		{
			g_shell->current = job;
			ft_putendl(job->command);
			continue_job(job, 1);
			return (0);
		}
		job = job->next;
	}
	ft_dprintf(STDERR_FILENO, JOB_ERR_NOTFOUND, "fg", s);
	return (1);
}

int	fg_builtin(char **argv)
{
	if (argv[0] && argv[1])
		ft_dprintf(STDERR_FILENO, STR_ARG_ERR, "fg");
	else if (!*argv)
		return (raise_current());
	else
		return (raise_job(*argv));
	return (1);
}
