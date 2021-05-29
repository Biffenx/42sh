/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:49:22 by srouhe            #+#    #+#             */
/*   Updated: 2021/05/29 15:55:21 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		token_del(t_token *token)
{
    ft_strdel(&token->data);
    if (token->heredoc)
        free(token->heredoc);
    free(token);    
}

static void		converge_lexers(t_lexer *lexer_old, t_lexer *lexer_new, \
                                    t_token **token)
{
	t_token		*head;
    t_token		*prev;
	t_token		*next;
    t_token		*als;

	head = lexer_old->head;
	while (lexer_old->head)
	{
		if (*token == lexer_old->head)
		{
            als = lexer_old->head;
            prev = lexer_old->head->prev;
            next = lexer_old->head->next;
            if (prev)
                prev->next = lexer_new->head;
            else
                head = lexer_new->head;
            lexer_new->last->next = next;
            token_del(als);
		}
		lexer_old->head = lexer_old->head->next;
	}
	lexer_old->last = lexer_old->head;
	lexer_old->head = head;
    lexer_old->first = head;
	lexer_old->flags |= lexer_new->flags;
	lexer_old->count += lexer_new->count - 1;
}

/*
** Create a new lexer for alias tokenization and converge it with the original lexer
*/

void			tokenize_alias(t_lexer *lexer, t_token **token, t_shell *shell)
{
	char		*value;
	t_lexer		lexer_als;

	ft_bzero(lexer_als.data, ARG_MAX);
	lexer_als.flags = 0;
	lexer_als.count = 0;
	lexer_als.head = NULL;
	lexer_als.first = NULL;
	lexer_als.last = NULL;
	if (shell->alias_index != 0)
		return;
	value = hash_get(shell->alias, (*token)->data);
	if (value)
	{
		tokenize(&lexer_als, value);
		converge_lexers(lexer, &lexer_als, token);
		shell->alias_index = 1;
	}
}
