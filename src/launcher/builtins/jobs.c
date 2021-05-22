/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:52:54 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/22 13:33:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/jobs.1p.html
*/

static char	**parse_options(char **argv, int *options)
{
	int i;
	int	j;

	*options = 0;
	i = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'p')
				*options = 1 << 0;
			else if (argv[i][j] == 'l')
				*options = 1 << 1;
			j += 1;
		}
		i += 1;
	}
	return (argv + i);
}

static int	print_all(int options)
{
	t_job	*job;

	job = g_shell->jobs;
	while (job)
	{
		if (options & 1 << 0)
			ft_printf("%d\n", job->pgid);
		else if (options & 1 << 1)
			ft_printf("[%i]%c %d %s %s\n", job->id, current(job), job->pgid, state(job), job->command);
		else
			ft_printf("[%i]%c %s %s\n", job->id, current(job), state(job), job->command);
		job = job->next;
	}
	return (0);
}

int jobs_builtin(char **argv)
{
	int	options;

	parse_options(argv, &options);
	if (!*argv)
		return (print_all(options));
	return (0);
}
