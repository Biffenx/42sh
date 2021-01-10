/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:44:17 by snake             #+#    #+#             */
/*   Updated: 2020/10/15 14:57:09 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void     append_job(t_job **head, t_job *new)
{
    t_job   *tmp;

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

static int      check_bg_fg(t_token **tokens)
{
    t_token *tmp;
    tmp = *tokens;
    while (tmp && !(tmp->type & T_SCOL))
    {
        if (tmp->type & T_BG)
            return (0);
        tmp = tmp->next;
    }
    return (1);
}

static t_job    *create_a_job(t_token **tokens, t_lexer **lexer)
{
    t_job   *job;

    if (*tokens == NULL)
        return (NULL);
	else if (!(job = ft_memalloc(sizeof(t_job))))
		return (NULL);
    job->cmd = ft_strdup((*tokens)->data);
    job->foreground = check_bg_fg(tokens);
    job->first_process = create_process_list(tokens);  
    job->pgid = 0;
    job->notified = 0;
    job->in = 0;
    job->out = 1;
    job->err = 2;
    job->next = NULL;
    return (job);
}

/*
** Create job struct list from lexer tokens
*/

t_job   *create_jobs(t_lexer **lexer)
{
    t_job   *head;
    t_job   *job;
    t_token *tokens;

    if (!lexer || !*lexer)
        return (NULL);
    head = NULL;
    tokens = (*lexer)->head;
    while (1)
    {
        if ((job = create_a_job(&tokens, lexer)) == NULL)
            break ;
        append_job(&head, job);
    }
    return (head);
}
