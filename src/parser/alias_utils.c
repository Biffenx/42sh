/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:43:12 by srouhe            #+#    #+#             */
/*   Updated: 2021/08/02 19:43:44 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	token_del(t_token *token)
{
	ft_strdel(&token->data);
	if (token->heredoc)
		free(token->heredoc);
	free(token);
}