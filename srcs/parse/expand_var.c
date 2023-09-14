/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:55:09 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/14 11:16:25 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_variables(t_config *data)
{
	t_tokens	*head;
	char		*expanded_value;

	head = data->tokens;
	while (data->tokens)
	{
		if (*data->tokens->value == '\'')
		{
			data->tokens = data->tokens->next;
			continue ;
		}
		expanded_value = replace_variables(data->tokens->value, data->env);
		if (expanded_value)
		{
			free(data->tokens->value);
			data->tokens->value = expanded_value;
		}
		data->tokens = data->tokens->next;
	}
	data->tokens = head;
}
