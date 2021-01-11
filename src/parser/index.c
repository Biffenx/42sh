/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:24:20 by srouhe            #+#    #+#             */
/*   Updated: 2021/01/11 20:04:45 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Prompt for more input with trailing pipe
*/

// static int	trailing_pipe(t_lexer **lexer)
// {
// 	char	*input;
// 	t_line	*line;

// 	line = create_line_editor();
// 	if (!(input = read_more(line, 0)))
// 		return (PARSER_ERROR);
// 	add_token(*lexer, input, STRING);
// 	free_line_editor(line);
// 	return (PARSER_OK);
// }

/*
**	1 - check lexer and token count
**	2 - check syntax
**	3 - check open quoting and read more
**	4 - check heredoc and read to all of them
**  5 - check trailing semicolon, pipe
**	6 - expand $ ~
*/

int			parser(t_lexer *lexer, t_shell *shell)
{
	int		r;

	if (!lexer || !lexer || !lexer->count)
		return (PARSER_ERROR);
	if ((r = check_syntax(lexer)) == PARSER_ERROR)
		return (PARSER_ERROR);
	if (lexer->flags & T_SQUOT)
	 	r = open_quote(lexer, S_QUOTE, shell);
	else if (lexer->flags & T_DQUOT)
	 	r = open_quote(lexer, D_QUOTE, shell);
	else if (lexer->flags & T_DLARR)
	 	r = check_heredoc(lexer, shell);
	if (lexer->count > 1 && r == PARSER_OK)
	{
		if (lexer->last->type & T_SCOL)
			r = remove_last_token(lexer);
		// else if ((*lexer)->last->type & T_PIPE)
		// 	r = trailing_pipe(lexer);
	}
	if (r == PARSER_OK)
		expand_tokens(lexer, shell);
	return (r);
}
