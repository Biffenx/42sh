/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:33:21 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/01 15:01:44 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void set_redir_tokens(t_re_ag *new, t_token *token)
{
	if (token && token->type & IO_NUM && ft_strequ(token->data, ft_itoa(STDERR_FILENO)))
		new->node.t_re.redir = ft_strjoin(ft_strdup(token->data), 
												ft_strdup(token->next->data));
	else
		new->node.t_re.redir = ft_strdup(token->next->data);
	new->node.t_re.file = ft_strdup(token->next->next->data);
	write_heredoc(new, token->next);
}


void set_aggre_tokens(t_re_ag *new, t_token *token)
{
	if (token && token->type & IO_NUM)
		new->node.t_ag.n = ft_strdup(token->data);
	else
		new->node.t_ag.n = ft_strdup("1");
	new->node.t_ag.sign = ft_strdup(token->next->data);
	new->node.t_ag.word = ft_strdup(token->next->next->data);
}

void set_re_ag_e_flag(t_re_ag *new, t_token *token)
{
	if (token->type & MASK_RE)
		new->e_flag = REDIR;
	else
		new->e_flag = AGGRE;
}