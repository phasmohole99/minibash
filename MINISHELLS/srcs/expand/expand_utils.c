/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:27:57 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/09 23:27:58 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_string(int str_len, char *data)
{
	t_token	*s;
	char	*string;

	s = (t_token *)malloc(sizeof(t_token));
	s->string = calloc(str_len + 1, sizeof(char));
	s->j = 0;
	s->check = 0;
	s->len = 0;
	while (data[s->j])
	{
		if (data[s->j] == '\'' && ++s->j)
			ft_skip(s, data);
		else if (data[s->j] == '$' && ++s->j)
			ft_help_get_str(data, s);
		else
		{
			s->string[s->len] = data[s->j];
			s->len++;
			s->j++;
		}
	}
	s->string[s->len] = '\0';
	string = ft_free_new_str(s);
	return (string);
}

void	ft_help_get_str(char *data, t_token *s)
{
	char	*string;

	string = NULL;
	if (ft_is_valid(data[s->j]) == 0)
	{
		s->string[s->len] = data[s->j];
		s->len++;
	}
	else
	{
		if (ft_hundling(s, data, string) == 1)
			return ;
	}
}

void	ft_skip(t_token *s, char *data)
{
	s->string[s->len] = '\'';
	s->len++;
	while (data[s->j] && data[s->j] != '\'')
	{
		s->string[s->len] = data[s->j];
		s->len++;
		s->j++;
	}
	s->string[s->len] = '\'';
}

void	ft_remove_quote(t_node *head)
{
	t_node	*node;
	char	*string;

	node = head;
	while (node)
	{
		string = malloc(sizeof(char *) * ft_strlen(node->data) + 1);
		string = ft_if_remove(node->data, string);
		free(node->data);
		node->data = string;
		node->quote = 1;
		node = node->next;
	}
}

void	ft_quote(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->args)
			ft_remove_quote(tmp->args);
		if (tmp->out_reds)
			ft_remove_quote(tmp->out_reds);
		if (tmp->in_reds)
			ft_remove_quote(tmp->in_reds);
		if (tmp->her_reds)
			ft_remove_quote(tmp->her_reds);
		tmp = tmp->next;
	}
}