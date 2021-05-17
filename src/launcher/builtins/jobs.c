/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:52:54 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/17 08:03:43 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/jobs.1p.html
*/

static int	parse_options(char **argv, int *i)
{
	int	options;
	int	j;

	options = 0;
	j = 0;
	while (argv[*i] && argv[*i][j] == '-')
	{
		while (argv[*i][j])
		{
			if (argv[*i][j + 1] == 'l')
				options |= 1 << 0;
			else if (argv[*i][j + 1] == 'p')
				options |= 1 << 1;
			j += 1;
		}
		*i += 1;
	}
	return (options);
}

static char	*state(t_job *job)
{
	if (job_is_completed(job))
		return ("Done");
	else if (job_is_stopped(job))
		return ("Stopped");
	else
		return ("Running");
}

static void	list_all(int options)
{
	t_job	*job;

	job = g_shell->jobs;
	while (job)
	{
		if (options & 1 << 0)
			ft_printf("[%i] %i %s %s\n", job->id, job->pgid, state(job), job->command);
		else if (options & 1 << 1)
			ft_printf("%i\n", job->pgid);
		else
			ft_printf("[%i] %s %s\n", job->id, state(job), job->command);
		job = job->next;
	}
}

static void	list_selected(int options, char **argv, int *i)
{
	t_job	*job;

	while (argv[*i])
	{
		job = g_shell->jobs;
		while (job)
		{
			if (job->id == ft_atoi(argv[*i]))
			{
				if (options & 1 << 0)
					ft_printf("[%i] %i %s %s\n", job->id, job->pgid, state(job), job->command);
				else if (options & 1 << 1)
					ft_printf("%i\n", job->pgid);
				else
					ft_printf("[%i] %s %s\n", job->id, state(job), job->command);
			}
			job = job->next;
		}
		*i += 1;
	}
}

int jobs_builtin(char **argv)
{
	int		options;
	int		i;

	i = 1;
	options = parse_options(argv, &i);
	if (g_debug)
	{
		ft_print_bits(options, 32);
		ft_printf("\n%s\n", argv[i]);
	}
	if (!argv[i])
		list_all(options);
	else
		list_selected(options, argv, &i);
	return (0);
}
