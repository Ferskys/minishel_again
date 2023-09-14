/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:44:30 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/14 10:37:35 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_tokens(t_config *data)
{
	int			i;
	t_tokens	*head;
	t_tokens	*current;
	t_tokens	*previous;

	if (!data->raw_tokens || !*data->raw_tokens)
		data->tokens = NULL;
	i = 0;
	head = ft_calloc(1, sizeof(*head));
	current = head;
	current->prev = NULL;
	while (data->raw_tokens[i])
	{
		current->value = ft_strdup(data->raw_tokens[i]);
		if (data->raw_tokens[i + 1])
			current->next = ft_calloc(1, sizeof(*head));
		previous = current;
		current = current->next;
		if (current)
			current->prev = previous;
		i++;
	}
	data->tokens = head;
}

static int	set_tok_indexes(t_tokens *tokens)
{
	t_tokens	*current;
	int			i;

	current = tokens;
	i = 0;
	while (current)
	{
		current->index = i;
		i++;
		current = current->next;
	}
	return (i);
}

void	categorize_tokens(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	set_tok_indexes(tokens);
	while (current)
	{
		current->type = get_token_type(current);
		if (current->type == REDTOKEN || current->type == OPTOKEN)
			if (token_is_error(current))
				current->type = ERRTOKEN;
		current = current->next;
	}
}

int	check_for_non_print(char *value)
{
	int	count;

	count = 0;
	while (value[count])
	{
		if (!ft_isprint(value[count]) && (value[count] != 0))
			return (0);
		count++;
	}
	return (1);
}

void	delete_empty_nodes(t_tokens **head)
{
	t_tokens	*current;
	t_tokens	*temp;

	current = *head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		if (temp->value == NULL || temp->value[0] == '\0')
		{
			if (temp->prev != NULL)
				temp->prev->next = temp->next;
			if (temp->next != NULL)
				temp->next->prev = temp->prev;
			if (temp == *head)
				*head = current;
			free(temp->value);
			free(temp);
		}
	}
}
