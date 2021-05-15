/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:33 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/15 09:47:53 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static void internal_variables(t_hash *map, char **env)
{
	int i;
	char	*key;
	char	*value;

	i = 0;
	while (i < HASH_SIZE)
	{
		map[i].key = NULL;
		map[i].value = NULL;
		i += 1;
	}
	i = 0;
	while (env[i])
	{
		key = env[i];
		value = ft_strchr(env[i], '=');
		*value = '\0';
		value += 1;
		hash_put(map, key, value);
		*ft_strchr(env[i], '\0') = '=';
		i += 1;
	}
}

static void	internal_alias(t_hash *map)
{
	hash_put(map, "greet", "echo Hello World!");
}

void		create_shell(char **env, t_shell *shell)
{
	shell->exit = 0;
	shell->env = env;
	internal_variables(shell->vars, env);
	internal_alias(shell->alias);
	ft_bzero(shell->history_file, PATH_MAX);
	ft_strlcat(shell->history_file, getenv("HOME"), PATH_MAX);
	ft_strlcat(shell->history_file, HISTORY_FILE, PATH_MAX);
}
