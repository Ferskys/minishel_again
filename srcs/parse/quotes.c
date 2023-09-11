/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:24:06 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:31:43 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_no_one(char *value, char one)
{
	int	i;

	i = 0;
	while (*value)
	{
		if (*value == one)
		{
			value++;
			continue ;
		}
		value++;
		i++;
	}
	return (i);
}

static void	copy_no_one(char *value, char *temp, char one)
{
	while (*value)
	{
		if (*value == one)
		{
			value++;
			continue ;
		}
		*temp = *value;
		value++;
		temp++;
	}
}

static char	*ft_unquote(char *value, char quote)
{
	char	*temp;

	temp = ft_calloc(count_no_one(value, quote) + 1, sizeof(char));
	copy_no_one(value, temp, quote);
	return (temp);
}

static void	transform_quotes(char *value)
{
	char	sinq;
	char	douq;

	sinq = 0;
	douq = 0;
	while (*value)
	{
		if (*value == '\"' && !douq)
		{
			sinq = (sinq + 1) % 2;
			*value = 1;
		}
		if (*value == '\'' && !sinq)
		{
			douq = (douq + 1) % 2;
			*value = 1;
		}
		value++;
	}
}

void	remove_quotes_from_tokens(t_tokens *tokens)
{
	t_tokens	*temp;
	char		*trimmed;

	temp = tokens;
	while (temp)
	{
		transform_quotes(temp->value);
		trimmed = ft_unquote(temp->value, 1);
		temp->value = safe_free(temp->value);
		temp->value = trimmed;
		temp = temp->next;
	}
}
