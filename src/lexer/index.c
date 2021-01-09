/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2021/01/09 17:33:23 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Add tokens to linked list:
**		Control tokens:
**			"&&", "||", "|", ";", ">>", "<<", "<&", "<>", "&>", ">|", ">", "<", "&"
**		Strings (parse quotes and dquotes)
**	Update count and flags to lexer
*/

void			tokenize(t_lexer *lexer, char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (ft_strchr(OPERATORS, input[i]))
			i += tokenize_operator(lexer, &input[i]);
		else if (!ft_strncmp(OPT_LEXER, &input[i], ft_strlen(OPT_LEXER) - 1))
		{
			lexer->flags |= DEBUG_LEXER;
			i += ft_strlen(OPT_LEXER);
		}
		else if (!ft_strncmp(OPT_JOBS, &input[i], ft_strlen(OPT_JOBS) - 1))
		{
			lexer->flags |= DEBUG_JOBS;
			i += ft_strlen(OPT_JOBS);
		}
		else if (is_valid_char(input[i]))
			i += tokenize_string(lexer, &input[i]);
		else
			i++;
	}
	lexer->first = lexer->head;
}
