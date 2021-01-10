/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:34:01 by srouhe            #+#    #+#             */
/*   Updated: 2021/01/10 13:43:13 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Remove last token
*/

int		remove_last_token(t_lexer *lexer)
{
	t_token *token;

	token = lexer->head;
	while (token->next->next)
		token = token->next;
	free(lexer->last->data);
	free(lexer->last);
	token->next = NULL;
	lexer->last = token;
	lexer->count--;
	return (PARSER_OK);
}

/*
** Jump to next operator
*/

int		next_operator(t_token *token, int type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type & type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** Remove quoting from input in case of squote or dquote
*/

void	remove_quotes(t_token *token, int wquote)
{
	char	*clean;
	t_token *tmp;

	clean = NULL;
	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	if (wquote == D_QUOTE)
		clean = ft_strreplace(tmp->data, "\"", "");
	else if (wquote == S_QUOTE)
		clean = ft_strreplace(tmp->data, "'", "");
	ft_strdel(&tmp->data);
	tmp->data = clean;
}
