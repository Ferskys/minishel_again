/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:07:00 by fsuomins          #+#    #+#             */
/*   Updated: 2023/07/22 00:00:39 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && !is_word)
		{
			is_word = 1;
			count++;
		}
		else if (*s == c && is_word)
			is_word = 0;
		s++;
	}
	return (count);
}

static size_t	ft_len(char *s, char c, size_t start)
{
	size_t	len;
	size_t	end;

	len = 0;
	end = 0;
	if (ft_strchr(&s[start], c))
		len = ft_strlen(ft_strchr(&s[start], c));
	else
		len = ft_strlen(&s[start]);
	end = ft_strlen(s) - len - start;
	if (!end)
		end = ft_strlen(&s[start]);
	return (end);
}

static void	transform_function(char *s, char c, char **tab)
{
	int	start;
	int	end;
	int	index;

	start = 0;
	end = 0;
	index = 0;
	while (s[start])
	{
		if (s[start] != c)
		{
			end = ft_len(s, c, start);
			tab[index] = ft_substr(s, start, end);
			index++;
			start += end;
		}
		else
			start++;
	}
	tab[index] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	transform_function((char *)s, c, tab);
	return (tab);
}
