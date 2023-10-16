/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:28:00 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/12 20:53:25 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"


void ft_mini_expen(t_tokenizer *token,char **env)
{
    t_tokenizer *cmd = token;
    
    while (cmd)
    {
        cmd->content = get_expand(cmd->content,env);
        cmd = cmd->next;
    }
}

char *get_expand(char *content,char **env)
{
    int len = get_str_len(content,env);
    char *str = get_new_string(len,content,env);
    free(content);
    return (str);
}


// int j ,len;
// char *value ,*id;
int get_str_len(char* data,char **env)
{
    t_tokenizer s;

    s.i = 0;
    s.len = 0;
    while(data[s.i])
    {
        if(data[s.i] && data[s.i] != '\'')
        {
            s.len++;
            s.i++;
        }
        else if (data[s.i] == '$' && ++s.i)
            ft_get_len(&s,data,env);
        else
        {
            s.len++;
            s.i++;
        }
    }
    return (s.len);
}

void ft_get_len(t_tokenizer *token,char *data,char **env)
{
    if(ft_valid(data[token->i]) == 0)
        token->len++;
    else
    {
        token->id=  get_index(&data[token->i]);
        token->var = get_var(token->id,env);
        if(!token->var)
        {
            free(token->id);
            return;
        }
        token->i = token->i + ft_strlen(token->id);
        token->len = token->len + ft_strlen(token->var);
        free(token->id);
    }
}

void expand(t_data *data)
{
    t_tokenizer *cmd = data->tokenizer;

    while (cmd)
    {
        ft_mini_expen(cmd,data->env);
        if(cmd->type == RED_IN)
            ft_mini_expen(cmd,data->env);
        if(cmd->type == RED_OUT_APPEND 
        || cmd ->type == RED_OUT_TRUNC)
            ft_mini_expen(cmd,data->env);
        cmd = cmd->next;
    }
}
