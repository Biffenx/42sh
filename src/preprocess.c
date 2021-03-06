/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:59:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/06 14:47:07 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		append_job(t_job **head, t_job *new)
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

static void		launcher(t_job *job)
{
	while (job)
	{
		launch_job(job, job->foreground);
		job = job->next;
	}
	do_job_notification();
}

static void		loader(t_lexer *lexer)
{
	t_token		*tokens;
	t_job		*job;

	tokens = lexer->head;
	job = create_job(&tokens);
	append_job(&g_shell->jobs, job);
	while (tokens)
		append_job(&g_shell->jobs, create_job(&tokens));
	if (lexer->flags & DEBUG_JOBS)
		job_debug(job);
	launcher(job);
}

void			preprocess(char *input, t_shell *shell)
{
	t_lexer		lexer;

	lexer.head = NULL;
	lexer.first = NULL;
	lexer.last = NULL;
	lexer.count = 0;
	lexer.flags = 0;
	tokenize(&lexer, input);
	if (lexer.flags & DEBUG_LEXER)
		lexer_debug(lexer);
	else
		parser(&lexer, shell) == PARSER_OK ? loader(&lexer) : PASS;
	lexer_del(&lexer);
}
