/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:44:21 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:31:43 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	iterate_through_quotes(t_split_shell *splitter)
{
	char	first_char;

	first_char = *splitter->temp;
	if (first_char == '\'' || first_char == '\"')
	{
		if (splitter->temp[1])
			splitter->temp++;
		while (*splitter->temp && (*splitter->temp != first_char))
			splitter->temp++;
		if (*splitter->temp == first_char)
			splitter->temp++;
	}
}

static int	count_till_quo(char *temp)
{
	char	quote;
	int		count;

	count = 0;
	quote = *temp;
	while (temp[count] && (temp[count] != quote || !count))
	{
		count++;
	}
	if (temp[count] == quote)
	{
		count++;
	}
	return (count);
}

static int	get_word_size(char *str, char delimiter)
{
	char	*temp;
	int		size;
	int		ret;

	temp = str;
	size = 0;
	ret = 0;
	while (*temp && *temp == delimiter)
		temp++;
	while (*temp && *temp != delimiter)
	{
		if (*temp == '\'' || *temp == '\"')
		{
			size = count_till_quo(temp);
			temp += size;
			ret += size;
		}
		else
		{
			temp++;
			ret++;
		}
	}
	return (ret);
}

static void	copy_to_split(char *split, t_split_shell *splitter)
{
	int	i;

	i = 0;
	while (i < splitter->size_of_word)
	{
		split[i] = *splitter->temp;
		splitter->temp++;
		i++;
	}
}

char	**create_tokens_args(char *str, char delimiter)
{
	char			**args;
	t_split_shell	*splitter;

	splitter = ft_calloc (1, sizeof(*splitter) + 1);
	splitter->delimiter = delimiter;
	splitter->string = str;
	count_words(splitter);
	args = ft_calloc ((splitter->words + 1), sizeof(char *));
	splitter->temp = splitter->string;
	while (splitter->splited_words < splitter->words)
	{
		while (*splitter->temp == splitter->delimiter)
			splitter->temp++;
		splitter->size_of_word = (get_word_size(splitter->temp, ' '));
		args[splitter->splited_words] = ft_calloc \
			(splitter->size_of_word + 1, 1);
		copy_to_split (args[splitter->splited_words], splitter);
		splitter->splited_words++;
	}
	splitter = safe_free(splitter);
	return (args);
}
