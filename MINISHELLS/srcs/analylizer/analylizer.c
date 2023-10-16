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

int	ft_valid(char c)
{
	return ((ft_isalnum(c)) || (c == '_') || (c = '?'));
}

char	*get_index(char *string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (string[i] >= '0' && string[i] <= '9')
	{
		while (string[i] && (string[i] >= '0' && string[i] <= '9'))
			i++;
		j = i;
		while (string[j] && !ft_isdigit(string[i]))
			j++;
		return (ft_substr(string, i, j));
	}
	i = 0;
	if (string[i] && string[i] == '?')
		return (ft_substr(string, 0, i + 1));
	while (string[i] && (ft_isalnum(string[i]) || (string[i] == '?')))
		i++;
	return (ft_substr(string, 0, i));
}

// char	*get_value(char *id, t_env *envi)
// {
// 	t_env	*tmp;

// 	tmp = envi;
// 	while (tmp)
// 	{
// 		if ((ft_strlen(id) == ft_strlen(tmp->key))
// 			&& (ft_strncmp(id, tmp->key, ft_strlen(tmp->key)) == 0))
// 		{
// 			return (tmp->value);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

char *get_var(char *id, char **env) 
{
    int i;

    i = 0;
    while (env[i]) 
    {
        int j = 0;
        while (env[i][j] == id[j] && id[j] != '\0') 
            j++;
        if (env[i][j] == '=' && id[j] == '\0') 
            return &env[i][j + 1];

        i++;
    }

    return NULL;
}
