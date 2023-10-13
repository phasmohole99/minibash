/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:18:25 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/09 16:58:17 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_count_words(char const *s)
{
	int	i;
	int	cnt;
	int quote;
	int 	token;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i])
			cnt++;
		if (ft_strchr("<>|",s[i]) && s[i])
		{
			token = s[i++];
			while (s[i] == token)
				++i;
		}
		else
		{
			while(!ft_strchr("<|>",s[i]) && s[i] && s[i] != ' ')
			{
				quote = 0;
				if (s[i] == 34 || s[i] == 39)
					quote = s[i++];
				while (quote && s[i] != quote)
					i++;
				++i;
			}
		}
	}
	return (cnt);
}

void	fill_s(char **dest, char const *s, char c, int words_nbr)
{
	int	i;
	int	j;
	int quote;
	int token;

	(void)c;
	j = 0;
	while (j < words_nbr)
	{
		i = 0;
		while (*s && *s == ' ')
			++s;
			if (ft_strchr("<>|",s[i]) && s[i])
			{
				token = s[i++];
				while (s[i] == token)
					++i;
			}
			else
			{
				while(!ft_strchr("<|>",s[i]) && s[i] && s[i] != ' ')
				{
					quote = 0;
					if (s[i] == 34 || s[i] == 39)
						quote = s[i++];
					while (quote && s[i] != quote)
						i++;
					++i;
				}
			}
			dest[j] = ft_substr(s, 0, i);
		j++;
		s += i;
	}
	dest[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		count_word;

	if (!s)
		return (NULL);
	count_word = ft_count_words(s);
	dest = malloc(sizeof(char *) * (count_word + 1));
	if (!dest)
		return (NULL);
	fill_s(dest, s, c, count_word);
	return (dest);
}
