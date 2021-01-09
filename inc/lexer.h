/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:56:02 by srouhe            #+#    #+#             */
/*   Updated: 2021/01/09 17:38:07 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
** Token flags
*/

# define T_AND_IF		(1 << 0)
# define T_OR_IF		(1 << 1)
# define T_PIPE			(1 << 2)
# define T_SCOL			(1 << 3)
# define T_DRARR		(1 << 4)
# define T_DLARR		(1 << 5)
# define T_LESS_AND		(1 << 6)
# define T_BOTH			(1 << 7)
# define T_GREAT_AND	(1 << 8)
# define T_ARRPIPE		(1 << 9)
# define T_SRARR		(1 << 10)
# define T_SLARR		(1 << 11)
# define T_STR			(1 << 12)
# define T_SQUOT		(1 << 13)
# define T_DQUOT		(1 << 14)
# define IO_NUM			(1 << 15)
# define T_FILE			(1 << 16)
# define T_DASH			(1 << 17)
# define T_HEREDOC		(1 << 18)
# define DEBUG_LEXER	(1 << 19)
# define DEBUG_JOBS		(1 << 24)
# define T_BG			(1 << 21)
# define T_NOEXPAND		(1 << 22)

/*
** Token flag masks
*/

# define MASK_STR		0b1000000000000
# define MASK_OP 		0b1111
# define MASK_REDIR 	0b111111110000
# define MASK_RE		0b110000110000
# define MASK_AG		0b001111000000
# define MASK_CTRL		0b111111111111
# define MASK_CMD		0b10111000000000000
# define MASK_ECHO		0b111000000000000

/*
** Definitions for tokenizing
*/

# define OPERATORS 		";|<>&"
# define OPERATOR_ARR 	"&&", "||", "|", ";", ">>", "<<", "<&", "<>", ">&", ">|", ">", "<", "&"
# define OP_SLOTS		13
# define OP_LEN			3

/*
** Utils for adding correct flags to tokens
*/

# define STRING			12
# define F_SQUOTE		13
# define F_DQUOTE		14
# define D_QUOTE		34
# define S_QUOTE		39
# define IO_NUMBER		15
# define FILENAME		16
# define DASH			17
# define HEREDOC		18
# define BACKGROUND		21
# define NOEXPAND		22

# define OPT_LEXER		"--lexer"
# define OPT_JOBS		"--jobs"

typedef struct			s_token
{
	int					type;
	int					fd;
	char				*data;
	char				*heredoc;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct			s_lexer
{
	int					flags;
	int					count;
	struct s_token		*head;
	struct s_token		*first;
	struct s_token		*last;
}						t_lexer;

int						is_valid_char(char c);
int						next_quote(char *input, int q);
int						str_isnumeric(char *str);
int						tokenize_operator(t_lexer *lexer, char *input);
int						tokenize_string(t_lexer *lexer, char *input);
void					add_token(t_lexer *lexer, char *data, int flag);
void					tokenize(t_lexer *lexer, char *input);
void					lexer_del(t_lexer *lexer);
void					lexer_debug(t_lexer lexer);

#endif
