/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:30:02 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:35:05 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_is_builtin(char *value)
{
	if (!ft_strcmp(value, "echo"))
		return (1);
	if (!ft_strcmp(value, "cd"))
		return (1);
	if (!ft_strcmp(value, "pwd"))
		return (1);
	if (!ft_strcmp(value, "export"))
		return (1);
	if (!ft_strcmp(value, "unset"))
		return (1);
	if (!ft_strcmp(value, "env"))
		return (1);
	if (!ft_strcmp(value, "exit"))
		return (1);
	return (0);
}

int	token_is_operator(char *value)
{
	if (!ft_strcmp(value, "|"))
		return (1);
	if (!ft_strcmp(value, "||"))
		return (1);
	if (!ft_strcmp(value, "&"))
		return (1);
	if (!ft_strcmp(value, "&&"))
		return (1);
	if (!ft_strcmp(value, ";"))
		return (1);
	if (!ft_strcmp(value, "\\n"))
		return (1);
	return (0);
}

int	token_is_redirect(char *value)
{
	if (!ft_strcmp(value, ">"))
		return (1);
	if (!ft_strcmp(value, ">>"))
		return (1);
	if (!ft_strcmp(value, "<"))
		return (1);
	if (!ft_strcmp(value, "<<"))
		return (1);
	return (0);
}

int	token_is_word(t_tokens *temp)
{
	if (temp->value[0] == '\'' || temp->value[0] == '\"')
		return (1);
	if (check_for_non_print(temp->value))
		return (1);
	return (0);
}

int	token_is_command(t_tokens *temp)
{
	t_config	*data;

	data = get_data();
	if (!temp->prev && !temp->next)
		return (1);
	if (!temp->prev)
		return (1);
	if (temp->prev && temp->prev->type == OPTOKEN)
		return (1);
	if (temp->prev && temp->prev->type == FDTOKEN && \
		tok_get_path(temp->value, data->env))
	{
		if (temp->prev->prev && temp->prev->prev->type == REDTOKEN)
			return (1);
	}
	return (0);
}
