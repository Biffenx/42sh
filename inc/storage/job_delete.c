/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:01:51 by srouhe            #+#    #+#             */
/*   Updated: 2020/09/30 15:48:09 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void     re_ag_delete(t_re_ag *re_ag)
{
    t_re_ag   *tmp;

    while (re_ag)
    {
        tmp = re_ag;
        if (re_ag->e_flag == REDIR)
        {
            ft_strdel(&re_ag->node.t_re.redir);
            ft_strdel(&re_ag->node.t_re.file);
            re_ag->node.t_re.heredoc ? free(re_ag->node.t_re.heredoc) : PASS;
        }
        else
        {
            ft_strdel(&re_ag->node.t_ag.n);
            ft_strdel(&re_ag->node.t_ag.sign);
            ft_strdel(&re_ag->node.t_ag.word);
        }
        re_ag = re_ag->next;
        free(tmp);
    }   
}

static void     proc_delete(t_process *proc)
{
    t_process   *tmp;

    while (proc)
    {
        re_ag_delete(proc->re_ag);
        tmp = proc;
        ft_freestrarr(proc->cmds);
        ft_strdel(&(proc->path_join));
        proc = proc->next;
        free(tmp);
    }
}

void            jobs_delete(t_job **jobs)
{
    t_job   *tmp;

    if (!jobs || !*jobs)
        return ;
    while (*jobs)
    {
        proc_delete((*jobs)->first_process);
        tmp = *jobs;
        ft_strdel(&((*jobs)->cmd));
        *jobs = (*jobs)->next;
        free(tmp);
    }
}

void            job_delete(t_job **jobs)
{
    t_job   *tmp;

    if (!jobs || !*jobs)
        return ;
    proc_delete((*jobs)->first_process);
    tmp = *jobs;
    ft_strdel(&((*jobs)->cmd));
    *jobs = (*jobs)->next;
    free(tmp);
    tmp = NULL;
}