/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analylizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:44:04 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/12 20:43:05 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	analylizer(t_list *list)
{
    int pipe;
    t_list  *curr;

    curr = list;
    while(curr)
    {
        pipe = *curr->content == '|';
        if(*curr->content == '|' || *curr->content == '<' || *curr->content == '>')
        {
            if(ft_strlen(curr->content) > 1 && pipe)
                return (1);
            if (ft_strlen(curr->content) > 2)
                return (1);
            else if (!curr->next)
                return (1);
            else if (ft_strchr("<|>", *(curr->next->content)) && !pipe)
                return (1);
            else if (ft_strchr("|", *(curr->next->content)) && pipe)
                return (1);
        }
        else if (*curr->content == ';' || *curr->content == '&')
            return (1);
        curr = curr->next;
    }
	return (0);
}

int    check_quotes(char *line)
{
    int   single;
    int    d_quotes;

    single = 0;
    d_quotes = 0;
    while (*line)
    {
        if (*line == '\'' && !d_quotes)
        single = single;
        if (*line == '\"' && single)
            d_quotes = !d_quotes;
        line++;
    }
    return (single || d_quotes);
}