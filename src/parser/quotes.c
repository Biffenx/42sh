/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:21:20 by srouhe            #+#    #+#             */
/*   Updated: 2021/01/11 20:05:07 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*reader(t_shell *shell)
{
	reset(PROMPT_QUOTE, shell);
	editor(shell);
	return (shell->editor.buffer);
}

static void		read_open_quote(char **data, int wquote, t_shell *shell)
{
	char		*input;
	char		*tmp;
	int			flag;

	flag = 0;
	while ((input = reader(shell)) != NULL)
	{
		if (ft_lfind(input, wquote) != -1)
			flag = 1;
		tmp = *data;
		*data = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
		tmp = *data;
		*data = ft_strjoin(tmp, input);
		ft_strdel(&tmp);
		if (flag)
			break ;
	}
	if (!flag)
		ft_strdel(data);
}

/*
** Read in more input with open quotes
*/

int				open_quote(t_lexer *lexer, int wquote, t_shell *shell)
{
	char		err_msg;

	read_open_quote(&lexer->last->data, wquote, shell);
	if (lexer->last->data)
	{
		lexer->last->data[ft_strlen(lexer->last->data) - 1] = '\0';
		remove_quotes(lexer->head, wquote);
		return (PARSER_OK);
	}
	else
	{
		err_msg = (char)wquote;
		print_error(EOF_ERR, &err_msg);
		return (PARSER_ERROR);
	}
}
