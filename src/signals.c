/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 21:01:23 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 19:19:55 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void	signals(void)
{
	signal(SIGWINCH, signal_resize);
	signal(SIGINT, signal_interrupt);
}
