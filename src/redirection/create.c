/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:01:30 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 19:12:49 by jwilen           ###   ########.fr       */
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

static void	write_heredoc(t_re_ag *node, t_token *token)
{
	if (!(token->type & T_DLARR))
	{
		node->node.t_re.heredoc = NULL;
		return ;
	}
	node->node.t_re.heredoc = malloc(sizeof(int) * 2);
	pipe(node->node.t_re.heredoc);
	ft_dprintf(node->node.t_re.heredoc[1], token->heredoc);
	close(node->node.t_re.heredoc[1]);
}

static t_re_ag	*create_re_ag_node(t_token *token)
{
	t_re_ag	*new;

	if (!(new = ft_memalloc(sizeof(t_re_ag))))
		return (NULL);
	new->e_flag = token->type & MASK_RE ? REDIR : AGGRE;
	if (new->e_flag == REDIR)
	{
		new->node.t_re.redir = ft_strdup(token->data);
		new->node.t_re.file = ft_strdup(token->next->data);
		write_heredoc(new, token);
	}
	else
	{
		new->node.t_ag.n = token->prev->type & IO_NUM
			? ft_strdup(token->prev->data) : ft_strdup("1");
		new->node.t_ag.sign = ft_strdup(token->data);
		new->node.t_ag.word = ft_strdup(token->next->data);
	}
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
