/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:25:52 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:45:23 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "stdlib.h"

static int	get_cmd_size(t_token *token)
{
	int		i;

	i = 0;
	while (token && !(token->type & MASK_OP))
	{
		i++;
		token = token->next;
	}
	return (i);
}

char	**tokens_to_array(t_token **tokens)
{
	char	**array;
	int		i;

	i = 0;
	array = (char **)malloc(sizeof(char *) * (get_cmd_size(*tokens) + 1));
	if (!array)
		exit(1);
	while (*tokens && !((*tokens)->type & MASK_OP)
		&& !((*tokens)->type & MASK_REDIR))
	{
		if ((*tokens)->type & IO_NUM || (*tokens)->type & T_BG)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		array[i] = ft_strdup((*tokens)->data);
		i++;
		*tokens = (*tokens)->next;
	}
	array[i] = NULL;
	return (array);
}
