/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:52:54 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/17 13:55:31 by vkuokka          ###   ########.fr       */
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

static char	determine_current(t_job *job, char *current)
{
	if (job_is_stopped(job))
	{
		if (*current == '+')
		{
			*current = '-';
			return ('+');
		}
		else if (*current == '-')
		{
			*current = ' ';
			return ('-');
		}
	}
	return (' ');
}

static char	*determine_state(t_job *job)
{
	if (job_is_completed(job))
		return ("Done");
	else if (job_is_stopped(job))
		return ("Stopped");
	else
		return ("Running");
}

static void	list_all(int options, t_job *job, char *current)
{
	if (!job)
		return ;
	list_all(options, job->next, current);
	if (options & 1 << 0)
		ft_printf("[%i]%c %i %s %s\n", job->id, determine_current(job, current), job->pgid, determine_state(job), job->command);
	else if (options & 1 << 1)
		ft_printf("%i\n", job->pgid);
	else
		ft_printf("[%i]%c %s %s\n", job->id, determine_current(job, current), determine_state(job), job->command);
	job = job->next;
}

static void	list_selected(char **argv, int options, t_job *job, char *current)
{
	int i;

	i = 0;
	if (!job)
		return ;
	list_selected(argv, options, job->next, current);
	while (argv[i])
	{
		if (job->id == ft_atoi(argv[i]))
		{
			if (options & 1 << 0)
				ft_printf("[%i]%c %i %s %s\n", job->id, determine_current(job, current), job->pgid, determine_state(job), job->command);
			else if (options & 1 << 1)
				ft_printf("%i\n", job->pgid);
			else
				ft_printf("[%i]%c %s %s\n", job->id, determine_current(job, current), determine_state(job), job->command);
			return ;
		}
		i += 1;
	}
}

int jobs_builtin(char **argv)
{
	int		options;
	int		i;
	char	current;

	i = 1;
	current = '+';
	options = parse_options(argv, &i);
	if (g_debug)
	{
		ft_print_bits(options, 32);
		ft_printf("\n%s\n", argv[i]);
	}
	if (!argv[i])
		list_all(options, g_shell->jobs, &current);
	else
		list_selected(argv + i,  options, g_shell->jobs, &current);
	return (0);
}
