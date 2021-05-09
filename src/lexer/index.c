/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2021/05/09 11:38:34 by vkuokka          ###   ########.fr       */
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

void	tokenize(t_lexer *lexer, char *input)
{
	int	i;

	i = 0;
	ft_strcat(lexer->data, input);
	while (lexer->data[i] && ~g_shell->mode & INTERRUPT)
	{
		if (ft_strchr(OPERATORS, lexer->data[i]))
			i += tokenize_operator(lexer, &lexer->data[i]);
		else if (!ft_strncmp(OPT_LEXER, &lexer->data[i], ft_strlen(OPT_LEXER) - 1))
		{
			lexer->flags |= DEBUG_LEXER;
			i += ft_strlen(OPT_LEXER);
		}
		else if (!ft_strncmp(OPT_JOBS, &lexer->data[i], ft_strlen(OPT_JOBS) - 1))
		{
			lexer->flags |= DEBUG_JOBS;
			i += ft_strlen(OPT_JOBS);
		}
		else if (is_valid_char(lexer->data[i]))
			i += tokenize_string(lexer, &lexer->data[i]);
		else
			i++;
	}
	lexer->first = lexer->head;
}
