/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:03:47 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/10 13:43:35 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

# define PARSER_OK 		0
# define PARSER_ERROR 	1

int						check_syntax(t_lexer *lexer);
int						check_heredoc(t_lexer *lexer, t_shell *shell);
int						parser(t_lexer *lexer, t_shell *shell);
int						next_operator(t_token *token, int type);
int						open_quote(t_lexer *lexer, int wquote, t_shell *shell);
int						remove_last_token(t_lexer *lexer);
void					expand_tokens(t_lexer *lexer, t_shell *shell);
void					remove_quotes(t_token *token, int wquote);
void			        tokenize_alias(t_lexer **lexer, t_token **token);

#endif
