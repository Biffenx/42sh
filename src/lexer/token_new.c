/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:10:05 by srouhe            #+#    #+#             */
/*   Updated: 2020/04/18 13:05:32 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token	*new_token(char *data, int flag)
{
	t_token		*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	new->data = ft_strdup(data);
	new->heredoc = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->type |= (1 << flag);
	new->fd = 0;
	return (new);
}

/*
** Add new token to lexer, maintain connection both ways
*/

void			add_token(t_lexer *lexer, char *data, int flag)
{
	t_token	*token;
	t_token	*tmp;

	token = new_token(data, flag);
	if (!lexer->head)
	{
		lexer->head = token;
		lexer->last = token;
	}
	else
	{
		tmp = lexer->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		token->prev = tmp;
		lexer->last = token;
	}
	lexer->flags |= (1 << flag);
	lexer->count++;
	free(data);
}
