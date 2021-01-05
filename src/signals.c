/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:01:23 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/05 21:17:50 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell *g_shell;

static void	signal_resize(int signum)
{
	if (signum == SIGWINCH)
	{
		ioctl(1, TIOCGWINSZ, &g_shell->terminal.size);
		ioctl(1, TIOCSTI, "");
	}
}

static void	signal_interrupt(int signum)
{
	if (signum == SIGINT)
	{
		g_shell->mode = g_shell->mode | INTERRUPT;
		ioctl(1, TIOCSTI, "");
	}
}

void		signals(t_shell *shell)
{
	g_shell = shell;
	signal(SIGWINCH, signal_resize);
	signal(SIGINT, signal_interrupt);
    signal(SIGCHLD, SIG_DFL);
}