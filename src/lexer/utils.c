/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 09:45:18 by srouhe            #+#    #+#             */
/*   Updated: 2021/07/20 17:50:11 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_del(t_lexer *lexer)
{
	t_token	*tmp;
	t_token	*prev;

	if (!lexer)
		return ;
	tmp = lexer->first;
	while (tmp)
	{
		ft_strdel(&tmp->data);
		if (tmp->heredoc)
			free(tmp->heredoc);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
}

/*
**	Checks if c is printable, excluding spaces, operators, and escapes
*/

int	is_valid_char(char c)
{
	return ((c <= 126 && c > 32) && !ft_strchr(OPERATORS, c) && c != 92 ? 1 : 0);
}

/*
**	Jumps to next single or double quote
**	Returns -1 if matching quote is not found
*/

int	next_quote(char *input, int q)
{
	int	i;

	i = 0;
	if (ft_lfind(input, q) == -1)
		return (-1);
	while (input[i] && input[i] != q)
		i++;
	return (i);
}

/*
**	Checks if string contains only numeric characters
*/

int	str_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
