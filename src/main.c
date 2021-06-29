/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:47:31 by vkuokka           #+#    #+#             */
/*   Updated: 2021/06/29 19:04:08 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	termcaps(void)
{
	char	*type;
	char	buffer[2048];
	int		success;

	type = getenv("TERM");
	if (type == 0)
		write(2, TERM_ERR_ENV, ft_strlen(TERM_ERR_ENV));
	success = tgetent(buffer, type);
	if (success > 0)
		return ;
	else if (success < 0)
		write(2, TERM_ERR_DB, ft_strlen(TERM_ERR_DB));
	else if (success == 0)
		write(2, TERM_ERR_TYPE, ft_strlen(TERM_ERR_TYPE));
	exit(1);
}

static void	create_pgroup(t_shell *shell)
{
	pid_t	shell_pgid;

	if (shell->mode & INTERACTIVE)
	{
		while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
			kill(-shell_pgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		shell->pgid = getpid();
		if (setpgid(shell->pgid, shell->pgid) < 0)
		{
			write(2, SHELL_ERR_PGRP, ft_strlen(SHELL_ERR_PGRP));
			exit(1);
        }
		tcsetpgrp(STDIN_FILENO, shell->pgid);
	}
	shell->jobs = NULL;
	shell->current = NULL;
	shell->previous = NULL;
}

static void	terminal(t_terminal *terminal)
{
		if (tcgetattr(STDIN_FILENO, &terminal->original) == -1)
			exit(1);
		terminal->raw = terminal->original;
		terminal->raw.c_lflag &= ~(ICANON | ECHO);
}

static void	shell(void)
{
	t_shell	shell;

	shell.mode = isatty(STDIN_FILENO);
	create_shell(&shell);
	create_pgroup(&shell);
	if (shell.mode & INTERACTIVE)
	{
		terminal(&shell.terminal);
		signals();
		fetch(&shell);
	}
	g_shell = &shell;
	while (42)
	{
		get_autocomplete_commands(&shell);
		reset(PROMPT_NORMAL, &shell);
		editor(&shell);
		if (shell.mode & ENDOFFILE)
			break ;
		else if (!shell.editor.buffer[0] || shell.mode & INTERRUPT)
			continue ;
		preprocess(shell.editor.buffer, &shell);
	}
	save(&shell);
}

int		main(int argc, char **argv, char **env)
{
	if (!argc || !argv || !env)
		return (1);
	if (ft_strequ(argv[1], "--debug"))
		g_debug = 1;
	termcaps();
	tputs(tgetstr("cl", NULL), 1, &print_char);
	shell();
	return (0);
}
