/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:04:06 by srouhe            #+#    #+#             */
/*   Updated: 2021/05/07 16:02:44 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** If operator index is less than x, create normal token,
** 		otherwise create IO redirection
*/

static int	create_token(t_lexer *lexer, char *input, char *operator, int i)
{
	if (!ft_strncmp("&", operator, ft_strlen(operator)))
		i = BACKGROUND;
	if (i < 2)
	{
		add_token(lexer, ft_strdup(operator), i);
	}
	else
	{
		if (lexer->last && str_isnumeric(lexer->last->data))
		{
			input -= ft_strlen(operator) - 1;
			ft_isdigit(*input) ? lexer->last->type |= IO_NUM : PASS;
		}
		add_token(lexer, ft_strdup(operator), i);
	}
	return (ft_strlen(operator));
}

/*
** Loop through OPERATOR_ARR and create a new token with the correct operator.
*/

int			tokenize_operator(t_lexer *lexer, char *input)
{
	int			i;
	static char	operator[OP_SLOTS][OP_LEN] = {OPERATOR_ARR};

	i = 0;
	while (i < OP_SLOTS)
	{
		if (!ft_strncmp(input, operator[i], ft_strlen(operator[i])))
			return (create_token(lexer, input, operator[i], i));
		i++;
	}
	return (1);
}
