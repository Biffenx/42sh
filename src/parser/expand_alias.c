/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:49:22 by srouhe            #+#    #+#             */
/*   Updated: 2021/05/07 11:13:38 by vkuokka          ###   ########.fr       */
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
	int			i;
	char		*key;
	char		*val;
	t_hashmap		*als;
	t_lexer		lexer_als;

	i = 0;
	lexer_als.head = NULL;
	lexer_als.first = NULL;
	lexer_als.last = NULL;
	lexer_als.count = 0;
	lexer_als.flags = 0;
	als = hash_search(SH_ALIAS, shell);
	while (als->data[i])
	{
		key = split_key(als->data[i]);
		if (!ft_strcmp(key, (*token)->data))
		{
			val = split_val(als->data[i]);
			tokenize(&lexer_als, val);
			converge_lexers(lexer, &lexer_als, token);
			free(val);
		}
		free(key);
		i++;
	}
}
