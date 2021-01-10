/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:12:44 by srouhe            #+#    #+#             */
/*   Updated: 2020/10/01 13:34:17 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Check previous and current value of the token stack
**	And check if the current token is the last in the deck
*/

static int		check_stack(int prev, int curr, t_token *next)
{
	if (!prev && curr & MASK_OP)
		return (PARSER_ERROR);
	else if ((prev & MASK_REDIR || prev & MASK_OP) &&
			(curr & MASK_REDIR || curr & MASK_OP))
		return (PARSER_ERROR);
	else if ((curr & MASK_REDIR || curr & T_DLARR) && next == NULL)
		return (PARSER_ERROR);
	else if (curr & T_BG && next != NULL)
		return (PARSER_ERROR);
	return (PARSER_OK);
}

/*
**	Loop over tokens
**	Put their type on the int stack
**	Check the syntax
*/

int				check_syntax(t_lexer *lexer)
{
	int		top;
	int		stack[4096]; // dynamic allocation based on token count? hifistelyy
	t_token *token;

	top = 0;
	stack[top] = 0;
	token = lexer->head;
	while (token)
	{
		stack[++top] = token->type;
		if ((check_stack(stack[top - 1], stack[top], token->next)) == \
				PARSER_ERROR)
		{
			print_error(SYNTAX_ERR, token->data);
			return (PARSER_ERROR);
		}
		token = token->next;
	}
	return (PARSER_OK);
}
