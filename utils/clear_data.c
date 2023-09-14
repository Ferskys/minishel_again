/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:26:31 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/14 12:55:09 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clear_prompt(t_config *data)
{
	if (data->prompt)
	{
		if (data->parse)
			free(data->parse);
		if (data->raw_tokens)
			free_char_array(data->raw_tokens);
		if (data->tokens)
			destroy_token_list(data);
	}
}

static void	clear_parse(t_config *data)
{
	if (data->set_buffer_to_null)
		data->prompt = NULL;
	if (data->parse)
		free(data->parse);
	free_char_array(data->raw_tokens);
}

void	clear_data(t_config *data)
{
	data->tok_index = 0;
	if (data->state == PROMPT)
		clear_prompt(data);
	if (data->state == PARSE)
		clear_parse(data);
	if (data->state == EXECUTE)
	{
		if (data->tokens->value)
			destroy_token_list(data);
	}
	if (data->state == EXIT)
	{
		if (data->oldpwd)
			free(data->oldpwd);
		clear_env(data);
		rl_clear_history();
		close_inherited_fds();
	}
}
