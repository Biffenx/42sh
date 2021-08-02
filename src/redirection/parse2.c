/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:33:21 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/02 12:07:05 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/wait.h>


/*
**redirection to a file can either be truncate or append
*/

static int redir_is_truncate(char c)
{
	if (c == '\0')
		return 1;
	else
		return 0;
}

static int create_truncate_file(char *file)
{
	return (open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR));
}

static int create_append_file(char *file)
{
	return (open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR));
}

/*
** Closing heredoc write and setting heredoc read to programs fd in.
*/

static void	set_heredoc_fd(int *in, int *heredoc)
{
	close(heredoc[1]);
	if (*in != STDIN_FILENO)
		close(*in);
	*in = heredoc[0];
	dup2(*in, STDIN_FILENO);
	close(*in);
}

/*
** Setting programs outfile fd to opened file fd.
*/

static void	set_outfile_redirection_fd(int *outfile, char *file, char *redir)
{
	int fd;

	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	if (redir_is_truncate(redir[1]))
		fd = create_truncate_file(file);
	else
		fd = create_append_file(file);
	*outfile = fd;
	dup2(*outfile, STDOUT_FILENO);
	close(*outfile);
}

/*
** Setting programs in fd to opened file fd.
*/

static void	set_infile_redirection_fd(int *in, char *file)
{
	if (*in != STDIN_FILENO)
		close(*in);
	*in = open(file, O_RDONLY);
	dup2(*in, STDIN_FILENO);
	close(*in);
}

static void set_errfile_redirection_fd(int *err, char *file, char *redir)
{
	int fd;

	if (*err != STDERR_FILENO)
		close(*err);
	if (redir_is_truncate(redir[1]))
		fd = create_truncate_file(file);
	else
		fd = create_append_file(file);
	*err = fd;
	dup2(*err, STDERR_FILENO);
	close(*err);
}

/*
** Switch for redirection node
*/

void	switch_redir_node(t_re_ag *l, t_job *j, int *outfile)
{
	int		*heredoc;
	char	*file;
	char	*redir;

	heredoc = l->u_node.t_re.heredoc;
	file = l->u_node.t_re.file;
	redir = l->u_node.t_re.redir;
	if (redir[0] == '>')
		set_outfile_redirection_fd(outfile, file, redir);
	else if (redir[0] == '<' && !redir[1])
		set_infile_redirection_fd(&j->stdin, file);
	else if (redir[0] == '<' && redir[1] == '<' && !redir[2])
		set_heredoc_fd(&j->stdin, heredoc);
	else
		set_errfile_redirection_fd(&j->stderr, file, &redir[1]);
}
