/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:33:21 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/31 15:11:24 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/wait.h>

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
	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	*outfile = open(file, O_WRONLY | O_CREAT | (redir[1] == '\0' ?
	O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
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

/*
** Switch for redirection node
*/

void	switch_redir_node(t_re_ag *l, t_job *j, int *outfile)
{
	int		*heredoc;
	char	*file;
	char	*redir;

	heredoc = l->node.t_re.heredoc;
	file = l->node.t_re.file;
	redir = l->node.t_re.redir;
	if (redir[0] == '>')
	{
		set_outfile_redirection_fd(outfile, file, redir);
		dup42(STDIN_FILENO, *outfile, STDERR_FILENO);
	}
	else if (redir[0] == '<' && !redir[1])
		set_infile_redirection_fd(&j->stdin, file);
	else if (redir[0] == '<' && redir[1] == '<' && !redir[2])
		set_heredoc_fd(&j->stdin, heredoc);
//	else
//		ft_putendl("redir indexi 0 on numero?");
}
