/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:59:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/02/09 14:47:30 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		execute(t_lexer *lexer)
{
	if (lexer)
		return ;
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
