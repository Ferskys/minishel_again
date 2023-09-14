/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:13:28 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/14 10:40:37 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	expansions(t_config *data)
{
	expand_exit_code(data);
	expand_variables(data);
	expand_tilde(data);
}

void	parse(void)
{
	t_config	*data;

	data = get_data();
	remove_end_spaces(data);
	data->parse = add_spaces(data->prompt, data);
	data->raw_tokens = create_tokens_args(data->parse, ' ');
	create_tokens(data);
	expansions(data);
	delete_empty_nodes(&data->tokens);
	if (data->tokens && data->tokens->value)
	{
		categorize_tokens(data->tokens);
		swap_tokens(&data->tokens);
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
