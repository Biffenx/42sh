/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:01:30 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/01 14:49:27 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	append_re_ag(t_re_ag **head, t_re_ag *new)
{
	t_re_ag	*tmp;

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

static t_re_ag	*create_re_ag_node(t_token *token)
{
	t_re_ag	*new;

	if (!(new = ft_memalloc(sizeof(t_re_ag))))
		return (NULL);
	set_re_ag_e_flag(new, token);
	if (new->e_flag == REDIR)
		set_redir_tokens(new, token->prev);
	else
		set_aggre_tokens(new, token->prev);
	new->next = NULL;
	return (new);
}

/*
** Creates a helper list for a process
** containing its aggregations and redirections
*/

t_re_ag	*create_re_ag_list(t_token **tokens)
{
	t_re_ag	*head;
	t_re_ag	*re_ag;

	if (!tokens || !*tokens)
		return (NULL);
	head = NULL;
	while ((*tokens) && !((*tokens)->type & MASK_OP))
	{
		if ((*tokens)->type & MASK_REDIR)
		{
			re_ag = create_re_ag_node(*tokens);
			append_re_ag(&head, re_ag);
		}
		*tokens = (*tokens)->next;
	}
	return (head);
}
