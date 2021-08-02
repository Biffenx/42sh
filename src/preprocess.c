/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:59:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/31 15:26:27 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	append_job(t_job **head, t_job *new)
{
	t_job		*tmp;

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

static void	launcher(t_job *job)
{
	while (job && !job->launched)
	{
		launch_job(job, job->foreground);
		job = job->next;
	}
	do_job_notification();
}

static void	loader(t_lexer *lexer)
{
	t_token		*tokens;
	t_job		*job;

	tokens = lexer->head;
	job = create_job(&tokens);
	append_job(&g_shell->jobs, job);
	while (tokens)
		append_job(&g_shell->jobs, create_job(&tokens));
	if (lexer->flags & DEBUG_JOBS)
	{
		job_debug(job);
		return ;
	}
	if (~g_shell->mode & LOADJOB)
		launcher(job);
}

void	preprocess(char *input, t_shell *shell)
{
	t_lexer		lexer;

	ft_bzero(lexer.data, ARG_MAX);
	lexer.flags = 0;
	lexer.count = 0;
	lexer.head = NULL;
	lexer.first = NULL;
	lexer.last = NULL;
	tokenize(&lexer, input);
	if (~shell->mode & INTERRUPT)
	{
		if (parser(&lexer, shell) == PARSER_OK)
		{
			if (lexer.flags & DEBUG_LEXER)
				lexer_debug(lexer);
			else
				loader(&lexer);
		}
		add_entry(lexer.first, shell);
	}
	lexer_del(&lexer);
}
