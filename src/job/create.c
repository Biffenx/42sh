/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:43:18 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/07 17:57:51 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			append_process(t_process **head, t_process *new)
{
	t_process		*tmp;

	tmp = *head;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*head = new;
}

static char			*find_path(char *command)
{
	char			*path;
	size_t			i;
	char			**paths;

	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path = (char *)malloc(sizeof(char) * PATH_MAX);
	i = 0;
	while (g_shell->env[i] && !ft_strnequ(g_shell->env[i], "PATH=", 5))
		i += 1;
	paths = ft_strsplit(g_shell->env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		ft_bzero(path, PATH_MAX);
		ft_strcat(path, paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, command);
		ft_putendl(path);
		if (access(path, X_OK) == 0)
			break ;
		i += 1;
	}
	ft_arrfree(paths);
	return (path);
}

static t_process	*create_process(t_token **tokens)
{
	t_process		*process;

	process = (t_process *)malloc(sizeof(t_process));
	if (!process)
		exit(1);
	process->argv = tokens_to_array(tokens);
	process->path = find_path(process->argv[0]);
	// process->re_ag = create_re_ag_list(tokens);
	process->pid = 0;
	process->completed = 0;
	process->stopped = 0;
	process->status = 0;
	process->next = NULL;
	return (process);
}

static t_process	*list_process(t_token **tokens)
{
	t_process		*head;
	t_process		*process;

	head = NULL;
	while (1)
	{
		process = create_process(tokens);
		append_process(&head, process);
		if (*tokens == NULL)
			break;
		else if ((*tokens)->type & MASK_OP && !((*tokens)->type & T_SCOL))
			(*tokens) = (*tokens)->next;
		else if ((*tokens)->type & T_SCOL)
		{
			(*tokens) = (*tokens)->next;
			break;
		}
	}
	return (head);
}

static int			check_bg(t_token *tokens)
{
	t_token			*tmp;

	tmp = tokens;
	while (tmp && !(tmp->type & T_SCOL))
	{
		if (tmp->type & T_BG)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_job				*create_job(t_token **tokens)
{
	t_job			*job;

	job = (t_job *)malloc(sizeof(t_job));
	if (!job)
		exit(1);
	job->foreground = check_bg(*tokens);
	job->command = ft_strdup((*tokens)->data);
	job->first_process = list_process(tokens); 
	job->pgid = 0;
	job->notified = 0;
	job->stdin = STDIN_FILENO;
	job->stdout = STDOUT_FILENO;
	job->stderr = STDERR_FILENO;
	job->next = NULL;
	return (job);
}
