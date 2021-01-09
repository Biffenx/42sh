/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:59:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/09 17:41:15 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* static void		execute(t_lexer *lexer)
{
	t_job	*jobs;
	t_job	*first;

	if ((jobs = create_jobs(&lexer)) != NULL)
	{
		if (lexer->flags & DEBUG_JOBS)
			jobs_debug(jobs);
		else
		{
			first = jobs;
			while(first)
			{
				start_execution(first);
				first = first->next;
			}
		}
		if (job_is_completed(jobs))
			job_delete(&jobs);
	}
} */

void		preprocess(char *input, t_shell *shell)
{
	t_lexer	lexer;

	(void)shell;
	lexer.head = NULL;
	lexer.first = NULL;
	lexer.last = NULL;
	lexer.count = 0;
	lexer.flags = DEBUG_LEXER;
	tokenize(&lexer, input);
	if (lexer.flags & DEBUG_LEXER)
		lexer_debug(lexer);
	// else
	// 	parser(&lexer) == PARSER_OK ? PASS /*execute(lexer)*/ : PASS;
	lexer_del(&lexer);
}
