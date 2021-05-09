/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 17:03:47 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/09 17:01:19 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

# define PARSER_OK 		0
# define PARSER_ERROR 	1

int						check_syntax(t_lexer *lexer);
int						check_heredoc(t_lexer *lexer, t_shell *shell);
int						parser(t_lexer *lexer, t_shell *shell);
int						next_operator(t_token *token, int type);
int						remove_last_token(t_lexer *lexer);
void					expand_tokens(t_lexer *lexer, t_shell *shell);
void					tokenize_alias(t_lexer *lexer, t_token **token, t_shell *shell);
char					*split_val(const char *s);
char					*split_key(const char *s);
char					*parse_quotes(char *s);

#endif
