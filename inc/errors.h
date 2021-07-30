/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:12:17 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 13:53:08 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
** Map builtin.
*/

# define MAP_SYNTAX "42sh: map: syntax: map [function] [key]=value\n"
# define MAP_HELP "42sh: map: functions: get, put, delete, purge, display\n"

/*
** HASH builtin.
*/

# define HASH_SYNTAX "42sh: hash: syntax: hash [-r]\n"
# define HASH_ERR_OPT "42sh: hash: bad option: -%c\n"

/*
** Termcaps.
*/

# define TERM_ERR_ENV "Specify a terminal type.\n"
# define TERM_ERR_DB "Could not access the termcap data base.\n"
# define TERM_ERR_TYPE "Terminal type is not defined.\n"

/*
** Job control.
*/

# define SHELL_ERR_PGRP "Couldn't put the shell in its own process group.\n"
# define JOB_ERR_NOTFOUND "42sh: %s: %s: no such job\n"

/*
** Process.
*/

# define PROC_ERR_EXEC "Process launch failed.\n"

/*
** Fc builtin.
*/

# define FC_ERR_OPT "42sh: fc: bad option: -%c\n"
# define FC_ERR_EDIT "42sh fc: -e: option requires an argument\n"
# define FC_ERR_FD "42sh fc: could not open fcfile\n"
# define FC_ERR_EXEC "42sh fc: history events can't be executed backwards, aborted\n"
# define FC_ERR_EVENT "42sh fc: event not found: %s\n"
# define FC_ERR_REPL "42sh fc: replace argument invalid\n"
# define FC_SYNTAX "42sh: fc: syntax: \
fc [-r] [-e editor] [first [last]]\n \
fc -l [-nr] [first [last]]\n \
fc -s [old=new] [first]\n"

/*
** History builtin
*/

#define HIST_ERR_OPT "42sh: history: bad option: -%c\n"
#define HIST_SYNTAX	"42sh: history: syntax: history [-c]"

/*
** Core history.
*/

# define HIST_ERR_FILE "Could not open history file.\n"

/*
** General errors.
*/

# define STR_ARG_ERR "42sh: %s: too many arguments\n"

# define STR_MALLOC_ERR "42sh: malloc error."
# define STR_FORK_ERR "42sh: failed to create child process."
# define STR_EXECVE_ERR "42sh: execve error."
# define STR_SYNTAX_ERR "42sh: syntax error near unexpected token"
# define STR_PERMISSION_ERR "42sh: permission denied:"
# define STR_NOT_FOUND_ERR "42sh: No such file or directory"
# define STR_NOT_DIR_ERR "42sh: Not a directory"
# define STR_IS_DIR "42sh: is a directory:"
# define STR_PIPE_ERR "42sh: pipe error"
# define STR_DUP_ERR "42sh: dup error."
# define STR_REDIR_ERR "42sh: redirection error."
# define STR_AMB_REDIR_ERR "42sh: ambiguous redirection:"
# define STR_EOF_ERR "42sh: unexpected EOF while looking for matching"
# define STR_HERE_ERR "42sh: warning: here-document delimited by end-of-file"
# define STR_BAD_FD_ERR "42sh: Bad file descriptor:"

/*
** General error numbers.
*/

# define MALLOC_ERROR		2
# define FORK_ERR			3
# define EXECVE_ERROR		4
# define SYNTAX_ERR			5
# define PERMISSION_ERR 	6
# define NOT_FOUND_ERR		7
# define NOT_DIR_ERR		8
# define PIPE_ERR			9
# define DUP_ERR			10
# define REDIR_ERR			11
# define AMB_REDIR_ERR		12
# define EOF_ERR			14
# define HEREDOC_ERR		15
# define BAD_FD_ERR			16

#endif
