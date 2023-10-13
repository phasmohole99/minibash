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

<<<<<<< HEAD
#include "minishell.h"


// echo $USER
// node1 = echo 
// node2 = $USER

void	expand(t_cmd *cmd, t_env *envi)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		ft_mini_expen(tmp->args, envi);
		if (tmp->in_reds)
			ft_mini_expen(tmp->in_reds, envi);
		if (tmp->out_reds)
			ft_mini_expen(tmp->out_reds, envi);
		tmp = tmp->next;
	}
	ft_quote(cmd);
}

void	ft_mini_expen(t_node *node, t_env *envi)
{
	t_node	*tmp;

	tmp = node;
	while (tmp)
	{
		tmp->data = get_expanded(tmp->data, envi);
		tmp = tmp->next;
	}
}

char	*get_expanded(char *data, t_env *envi)
{
	char	*string;
	int		str_len;

	str_len = get_str_len(data, envi);
	string = get_new_string(str_len, data);
	free(data);
	return (string);
}

int	get_str_len(char *data, t_env *envi)
{
	t_token	s;

	s.j = 0;
	s.len = 0;
	while (data[s.j])
	{
		if (data[s.j] == '\'' && ++s.j)
		{
			while (data[s.j] && data[s.j] != '\'')
			{
				s.len++;
				s.j++;
			}
		}
		else if (data[s.j] == '$' && ++s.j)
			ft_help_get_len(&s, data, envi);
		else
		{
			s.len++;
			s.j++;
		}
	}
	return (s.len);
}

void	ft_help_get_len(t_token *s, char *data, t_env *envi)
{
	if (ft_is_valid(data[s->j]) == 0)
		s->len++;
	else
	{
		s->id = get_index(&data[s->j]);
		s->value = get_value(s->id, envi);
		if (!s->value)
		{
			free(s->id);
			return ;
		}
		s->j = s->j + ft_strlen(s->id);
		s->len = s->len + ft_strlen(s->value);
		free(s->id);
	}
}

// int expand_check(t_data *data,char **env)
// {
//     (void)env;
//     if()
// }


// void expand(t_data *data)
// {
//     t_data *curr = data;
    
    
// }
=======
#include "../../minishell.h"

// expand check if my data have $ in first word so i have expand it 
// check if the word in single quotes or double quotes


// check if have $ and 
// echo "$USER"
// 

// int check_ex(t_data *data)
// {
//     t_data *curr;
//     t_list *lst = data->lst;
    
//     curr = data;
//     while(lst)
//     {
//         if(ft_strcmp(lst->content,"$"))
//             value_env(curr->env,lst->content);
//         else
//             return 0;
//         lst = lst->next;
//     }
//     return 1;
// }

void expand(t_data *data) 
{
    if (data->tokenizer == NULL) 
        return;

    t_tokenizer *current = data->tokenizer;
    while (current != NULL) 
    {
        if (current->type == STRING && strstr(current->content, "$") != NULL) {
            char *ex_content = malloc(2 * strlen(current->content));
            ex_content[0] = '\0';

            char *token = strtok(current->content, "$");
            while (token != NULL)
            {
                char *envValue = getenv(token);
                if (envValue != NULL) {
                    strcat(ex_content, envValue);
                } else {
                    strcat(ex_content, "$");
                    strcat(ex_content, token);
                }
                token = strtok(NULL, "$");
            }

            free(current->content);
            current->content = ex_content;
            current->type = ENV_VARIABLE;
        }

        current = current->next;
    }
}
>>>>>>> df2bec8abe991d622d1aea564e699aaa5086c498
