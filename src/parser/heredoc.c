/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:09:11 by srouhe            #+#    #+#             */
/*   Updated: 2021/07/15 18:49:17 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*reader(t_shell *shell)
{
	reset(PROMPT_HEREDOC, shell);
	editor(shell);
	return (shell->editor.buffer);
}

//malloc problem at here forsure..
static char	*read_heredoc(char *r, char *d, t_shell *shell)
{
	char	*input;
	char	*tmp;

	while ((input = reader(shell)) != NULL && ~ g_shell->mode & INTERRUPT)
	{
		tmp = ft_strjoin(input, "\n");
		if (!ft_strncmp(tmp, d, ft_strlen(d)) || g_shell->mode & ENDOFFILE)
			return (r);
		if (!r)
			r = tmp;
		else
		{
			r = ft_realloc(r, ft_strlen(r), ft_strlen(r) + ft_strlen(tmp));
			r = ft_strncat(r, tmp, ft_strlen(tmp));
		}
	}
	r ? free(r) : PASS;
	return (NULL);
}

/*
** Read input in to [<<] and recurse to parser to check if more heredoc's
*/

int	check_heredoc(t_lexer *lexer, t_shell *shell)
{
	char	*new;
	t_token	*head;

	head = lexer->head;
	while (lexer->head)
	{
		if (lexer->head->type & T_DLARR && !lexer->head->heredoc)
		{
			if ((new = read_heredoc(lexer->head->heredoc, \
									lexer->head->next->data, shell)) != NULL)
			{
				lexer->head->heredoc = new;
				lexer->head = head;
				return (parser(lexer, shell));
			}
			else
			{
				~g_shell->mode & INTERRUPT ? print_error(HEREDOC_ERR,
					lexer->head->next->data): 0;
				return (PARSER_ERROR);
			}
		}
		lexer->head = lexer->head->next;
	}
	lexer->head = head;
	return (PARSER_OK);
}
