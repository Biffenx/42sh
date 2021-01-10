/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 03:07:17 by srouhe            #+#    #+#             */
/*   Updated: 2020/08/26 14:14:12 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void         append_proc(t_process **head, t_process *new)
{
    t_process   *tmp;

    tmp = *head;
    if (tmp)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    else
        *head = new;
}

static t_process    *create_proc(t_token **tokens)
{
    t_process   *process;

	if (!(process = ft_memalloc(sizeof(t_process))))
		return (NULL);
    // ft_printf("token %s\n", (*tokens)->data);
    process->cmds = tokens_to_array(tokens);
    process->e_factor = is_builtin(process->cmds);
    process->path_join = process->e_factor ? NULL : proc_path(process->cmds[0]);
    process->re_ag = create_re_ag_list(tokens);
    process->pid = 0;
    process->completed = 0;
    process->stopped = 0;
    process->status = 0;
    process->next = NULL;
    return (process);
}

t_process           *create_process_list(t_token **tokens)
{
    t_process   *head;
    t_process   *proc;

    head = NULL;
    while (1)
    {
        proc = create_proc(tokens);
        append_proc(&head, proc);
        if (*tokens == NULL)
            break ;
        else if ((*tokens)->type & MASK_OP && !((*tokens)->type & T_SCOL))
            *tokens = (*tokens)->next;
        else if ((*tokens)->type & T_SCOL)
        {
            *tokens = (*tokens)->next;
            break ;
        }
    }
    return (head);
}