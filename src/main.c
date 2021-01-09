/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:47:31 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/09 16:47:11 by vkuokka          ###   ########.fr       */
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
		write(2, "Specify a terminal type.", 25);
	success = tgetent(buffer, type);
	if (success > 0)
		return ;
	else if (success < 0)
		write(2, "Could not access the termcap data base.", 40);
	else if (success == 0)
		write(2, "Terminal type is not defined.", 30);
	exit(1);
}

static void	create_pgroup(t_shell *shell)
{
	pid_t	shell_pgid;

	if (shell->mode & INTERACTIVE)
	{
		write(1, "create process group\n", 22);
		return ;
		while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
			kill (- shell_pgid, SIGTTIN);
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, SIG_IGN);
		shell->pgid = getpid();
		if (setpgid (shell->pgid, shell->pgid) < 0)
		{
			write(2, "Couldn't put the shell in its own process group", 48);
			exit (1);
        }
		tcsetpgrp(STDIN_FILENO, shell->pgid);
		/* shell.jobs = NULL
		shell.jobs->head = NULL;
		shell.jobs->tail = NULL; */
	}
}

static void	terminal(t_terminal *terminal)
{
		if (tcgetattr(STDIN_FILENO, &terminal->original) == -1)
			exit(1);
		terminal->raw = terminal->original;
		terminal->raw.c_lflag &= ~(ICANON | ECHO);
}

static void	shell(char **env)
{
	t_shell	shell;

	shell.mode = isatty(STDIN_FILENO);
	shell.env = env;
	// create_shell(envp, editor); ?
	create_pgroup(&shell);
	// editor->ac = create_completer(); ?
	// load_runnables(editor->ac, editor->envp); ?
	// load_envs(editor->ac, editor->envp); ?
	// reset(NULL, editor); ?
	if (shell.mode & INTERACTIVE)
	{
		terminal(&shell.terminal);
		signals(&shell);
		fetch(&shell);
	}
	while (42)
	{
		reset(PROMPT_NORMAL, &shell);
		editor(&shell);
		if (shell.mode & ENDOFFILE)
			break ;
		else if (!shell.editor.buffer[0] || shell.mode & INTERRUPT)
			continue ;
		ft_printf("Input is: %s\n", shell.editor.buffer);
		add_entry(&shell);
		// preprocess(editor->buffer); ?
		// clean_paths(editor->ac); ?
	}
	save(&shell);
}

int		main(int argc, char **argv, char **env)
{
	if (!argc || !argv || !env)
		return (1);
	termcaps();
	tputs(tgetstr("cl", NULL), 1, &print_char);
	shell(env);
	return (0);
}
