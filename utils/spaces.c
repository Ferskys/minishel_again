/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:01:40 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:34:46 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_delimiter(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	count_words(t_split_shell *splitter)
{
	splitter->temp = splitter->string;
	while (*splitter->temp)
	{
		splitter->words++;
		while (*splitter->temp == splitter->delimiter)
			splitter->temp++;
		while (*splitter->temp && (*splitter->temp != splitter->delimiter))
		{
			if (*splitter->temp == '\'' || *splitter->temp == '\"')
				iterate_through_quotes(splitter);
			else
				splitter->temp++;
		}
	}
}
