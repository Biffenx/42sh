/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:43:11 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/10 22:13:22 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int run_builtin(char **argv)
{
	if (ft_strequ(argv[0], "fc"))
		return (fc(argv));
	if (ft_strequ(argv[0], "cd"))
		return (cd_builtin(argv));
	else if (ft_strequ(argv[0], "echo"))
		return (echo_builtin(argv));
	else if (ft_strequ(argv[0], "jobs"))
		return (jobs_builtin(argv));
	else if (ft_strequ(argv[0], "exit"))
		exit_builtin();
	return (1);
}