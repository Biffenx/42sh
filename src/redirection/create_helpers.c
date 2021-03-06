/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:33:21 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/02 12:07:05 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	write_heredoc(t_re_ag *node, t_token *token)
{
	if (!(token->type & T_DLARR))
	{
		node->u_node.t_re.heredoc = NULL;
		return ;
	}
	node->u_node.t_re.heredoc = malloc(sizeof(int) * 2);
	pipe(node->u_node.t_re.heredoc);
	ft_dprintf(node->u_node.t_re.heredoc[1], token->heredoc);
	close(node->u_node.t_re.heredoc[1]);
}

void set_redir_tokens(t_re_ag *new, t_token *token)
{
	if (token && token->type & IO_NUM && ft_atoi(token->data) == STDERR_FILENO)
		new->u_node.t_re.redir = ft_strjoin(ft_strdup(token->data), 
												ft_strdup(token->next->data));
	else
		new->u_node.t_re.redir = ft_strdup(token->next->data);
	new->u_node.t_re.file = ft_strdup(token->next->next->data);
	write_heredoc(new, token->next);
}


void set_aggre_tokens(t_re_ag *new, t_token *token)
{
	if (token && token->type & IO_NUM)
		new->u_node.t_ag.n = ft_strdup(token->data);
	else
		new->u_node.t_ag.n = ft_strdup("1");
	new->u_node.t_ag.sign = ft_strdup(token->next->data);
	new->u_node.t_ag.word = ft_strdup(token->next->next->data);
}

void set_re_ag_e_flag(t_re_ag *new, t_token *token)
{
	if (token->type & MASK_RE)
		new->e_flag = REDIR;
	else
		new->e_flag = AGGRE;
}