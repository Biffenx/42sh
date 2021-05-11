/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:33 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/11 10:29:52 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>

int		print_char(int c)
{
	return (write(0, &c, 1));
}

void		exit_error(int err, char *msg)
{
	err == MALLOC_ERROR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == FORK_ERR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == EXECVE_ERROR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == DUP_ERR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == REDIR_ERR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	err == PIPE_ERR ? ft_putendl_fd(msg, STDERR_FILENO) : PASS;
	exit(err);
}

void		print_error(int err, char *msg)
{
	if (err == SYNTAX_ERR)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", STR_SYNTAX_ERR, msg);
	else if (err == PERMISSION_ERR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_PERMISSION_ERR, msg);
	else if (err == NOT_FOUND_ERR)
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", msg, STR_NOT_FOUND_ERR);
	else if (err == NOT_DIR_ERR)
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", msg, STR_NOT_DIR_ERR);
	/* else if (err == EISDIR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_IS_DIR, msg); */ // NO ERNOS ALLOWED!!!
	else if (err == AMB_REDIR_ERR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_AMB_REDIR_ERR, msg);
	else if (err == PIPE_ERR)
		ft_dprintf(STDERR_FILENO, "%s\n", STR_PIPE_ERR);
	else if (err == EOF_ERR)
		ft_dprintf(STDERR_FILENO, "%s `%s'\n", STR_EOF_ERR, msg);
	else if (err == HEREDOC_ERR)
		ft_dprintf(STDERR_FILENO, "%s (wanted `%s')\n", STR_HERE_ERR, msg);
	else if (err == BAD_FD_ERR)
		ft_dprintf(STDERR_FILENO, "%s %s\n", STR_BAD_FD_ERR, msg);
}

static char	**init_env(char **env)
{
	int		i;
	int		size;
	char	**r;

	size = 0;
	while (env[size])
		size++;
	i = 0;
	if (!(r = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (env[i])
	{
		if (!(r[i] = ft_strdup(env[i])))
			return (NULL);
		i++;
	}
	r[size] = NULL;
	return (r);
}

static char **init_alias(void)
{
	char	**r;

	if (!(r = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	r[0] = ft_strdup("help=cat");
	r[1] = NULL;
	return (r);
}

void		create_shell(char **env, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		shell->dict[i] = NULL;
		i += 1;
	}
	shell->env = env;
	ft_bzero(shell->history_file, PATH_MAX);
	ft_strlcat(shell->history_file, getenv("HOME"), PATH_MAX);
	ft_strlcat(shell->history_file, HISTORY_FILE, PATH_MAX);
	hash_insert(SH_ENV, init_env(env), shell);
	hash_insert(SH_VARS, init_env(env), shell);
	hash_insert(SH_ALIAS, init_alias(), shell);
}