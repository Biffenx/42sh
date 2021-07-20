/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2021/07/20 12:42:01 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	1 - check lexer and token count
**	2 - check syntax
**	3 - check open quoting and read more
**	4 - check heredoc and read to all of them
**  5 - check trailing semicolon, pipe
**	6 - expand $ ~
*/

int	parser(t_lexer *lexer, t_shell *shell)
{
	int		r;

	if (!lexer || !lexer || !lexer->count)
		return (PARSER_ERROR);
	if ((r = check_syntax(lexer)) == PARSER_ERROR)
		return (PARSER_ERROR);
	else if (lexer->flags & T_DLARR)
		r = check_heredoc(lexer, shell);
	if (lexer->count > 1 && r == PARSER_OK)
	{
		if (lexer->last->type & T_SCOL)
			r = remove_last_token(lexer);
	}
	if (r == PARSER_OK)
		expand_tokens(lexer, shell);
	return (r);
}
