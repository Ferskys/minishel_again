/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:16:27 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 22:35:31 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_token_type(t_tokens *temp)
{
	int	type_is;

	type_is = ERRTOKEN;
	if (token_is_operator(temp->value))
		return (OPTOKEN);
	if (token_is_redirect(temp->value))
		return (REDTOKEN);
	if (token_is_fd(temp))
		return (FDTOKEN);
	if (token_is_word(temp))
		type_is = WORDTOKEN;
	if (token_is_command(temp) && type_is == WORDTOKEN)
		type_is = COMTOKEN;
	if (token_is_builtin(temp->value) && type_is == COMTOKEN)
		type_is = BITOKEN;
	return (type_is);
}

int	token_is_error(t_tokens *temp)
{
	if (temp->type == OPTOKEN && (!ft_strcmp(temp->value, "||")))
		return (1);
	if (temp->type == OPTOKEN && !temp->prev)
		return (1);
	if (temp->prev && temp->prev->type == REDTOKEN)
		if (temp->type == OPTOKEN || temp->type == REDTOKEN)
			return (1);
	if (temp->prev && temp->prev->type == OPTOKEN)
		if (temp->type == OPTOKEN)
			return (1);
	if ((temp->type == REDTOKEN || temp->type == OPTOKEN) && !temp->next)
		return (1);
	return (0);
}

int	token_is_fd(t_tokens *temp)
{
	if (temp->prev && temp->prev->type == REDTOKEN)
		return (1);
	else if (temp->prev && temp->prev->type == FDTOKEN && !ft_strncmp(temp->value, "./", 2))
		return (1);
	return (0);
}
