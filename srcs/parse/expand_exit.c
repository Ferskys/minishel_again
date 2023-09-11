/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:50:50 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:31:12 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_mouli(void *a, void *b)
{
	free(a);
	free(b);
	a = NULL;
	b = NULL;
}

char	*find_exit_code(char *str)
{
	while (*str)
	{
		if (*str == '$' && str[1] == '?')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*update_token_exit_code(char *str, char *exit_code, char *var_head)
{
	char	*part1;
	char	*final_str;

	part1 = ft_strjoin(str, exit_code);
	final_str = ft_strjoin(part1, var_head + 2);
	free(part1);
	return (final_str);
}

void	process_token(t_config *data, t_tokens *token)
{
	char	*ptr;
	char	*exit_str;
	char	*current;

	ptr = find_exit_code(token->value);
	if (ptr)
	{
		*ptr = '\0';
		exit_str = ft_itoa(data->exit_code);
		current = token->value;
		token->value = update_token_exit_code(token->value, exit_str, ptr);
		free_mouli(exit_str, current);
	}
}

void	expand_exit_code(t_config *data)
{
	t_tokens	*head;

	head = data->tokens;
	while (head)
	{
		if (*head->value == '\'')
		{
			head = head->next;
			continue ;
		}
		process_token(data, head);
		head = head->next;
	}
}
