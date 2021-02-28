/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:10:44 by vkuokka           #+#    #+#             */
/*   Updated: 2021/02/28 13:02:00 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_debug(t_lexer lexer)
{
	ft_printf("%s: [%d]\n", "token count", lexer.count);
	ft_printf("flags: ");
	ft_print_bits(lexer.flags, 24);
	ft_putchar('\n');
	while (lexer.head)
	{
		ft_printf("%s: [%s] type: [%d]\n", "token", \
					lexer.head->data, lexer.head->type);
		if (lexer.head == lexer.last)
			break ;
		lexer.head = lexer.head->next;
	}
}
