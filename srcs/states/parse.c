/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:13:28 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/13 20:39:29 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_tilde(t_config *data)
{
	t_tokens	*current;
	char		*home_dir;
	char		*new_value;

	current = data->tokens;
	home_dir = getenv("HOME");
	while (current != NULL)
	{
		if (current->type == WORDTOKEN && current->value[0] == '~')
		{
			if (home_dir == NULL)
				new_value = ft_strdup(current->value);
			else
				new_value = ft_strjoin(home_dir, current->value + 1);
			free(current->value);
			current->value = new_value;
		}
		current = current->next;
	}
}

static void	remove_end_spaces(t_config *data)
{
	char	*str;

	str = ft_strtrim(data->prompt, " ");
	if (str)
	{
		free(data->prompt);
		data->prompt = str;
	}
	if (*str == '#')
	{
		data->state = PROMPT;
		return ;
	}
}

void	print_t_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("type: %d\n", tokens->type);
		printf("value: %s\n", tokens->value);
		tokens = tokens->next;
	}
}

static void	delete_nodes_with_null_or_empty_value(t_tokens **head)
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

void	check_heredoc(t_config *data)
{
	t_tokens	*current;
	char		*heredoc_file;

	current = data->tokens;
	while (current != NULL)
	{
		if (current->type == REDTOKEN && strcmp(current->value, "<<") == 0)
		{
			free(current->value);
			current->value = ft_strdup("<");
			heredoc_file = redirect_heredoc(current->next->value);
			if (heredoc_file)
			{
				free(current->next->value);
				current->next->value = heredoc_file;
			}
			else
				data->state = PROMPT;
		}
		current = current->next;
	}
}

void	parse(void)
{
	t_config	*data;

	data = get_data();
	remove_end_spaces(data);
	data->parse = add_spaces(data->prompt, data);
	data->raw_tokens = create_tokens_args(data->parse, ' ');
	create_tokens(data);
	expand_exit_code(data);
	expand_variables(data);
	expand_tilde(data);
	delete_nodes_with_null_or_empty_value(&data->tokens);
	if (data->tokens && data->tokens->value)
	{
		categorize_tokens(data->tokens);
		check_and_wap_nodes(&data->tokens);
		remove_duplicate_fd(&data->tokens);
		remove_quotes_from_tokens(data->tokens);
		categorize_tokens(data->tokens);
		ignore_signals();
		check_heredoc(data);
		set_signal();
	}
	else
		data->state = PROMPT;
	clear_data(data);
	if (data->state == PARSE)
		data->state = EXECUTE;
}
