/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:43:11 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/14 12:27:47 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int run_builtin(char **argv)
{
	if (ft_strequ(argv[0], "exit"))
		shell_exit();
	else if (ft_strequ(argv[0], "jobs"))
		return (jobs(argv));
	else if (ft_strequ(argv[0], "fc"))
		return (fc(argv));
	return (1);
}