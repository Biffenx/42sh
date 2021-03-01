/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:59:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/01 19:56:46 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void append_job(t_job **head, t_job *new)
{
	t_job *tmp;

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

static void		execute(t_lexer *lexer)
{
	t_token		*tokens;
	t_job		*job;

	tokens = lexer->head;
	while (tokens)
	{
		job = create_job(&tokens);
		append_job(&g_shell->jobs, job);
	}
	if (lexer->flags & DEBUG_JOBS)
		job_debug();
}

void		preprocess(char *input, t_shell *shell)
{
	t_lexer	lexer;

	lexer.head = NULL;
	lexer.first = NULL;
	lexer.last = NULL;
	lexer.count = 0;
	lexer.flags = 0;
	tokenize(&lexer, input);
	if (lexer.flags & DEBUG_LEXER)
		lexer_debug(lexer);
	else
		parser(&lexer, shell) == PARSER_OK ? execute(&lexer) : PASS;
	lexer_del(&lexer);
}
