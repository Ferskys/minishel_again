/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:06:48 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/14 12:49:02 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_config	*get_data(void)
{
	static t_config	data;

	return (&data);
}

void	close_inherited_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	*destroy_token_list(t_config *data)
{
	t_tokens	*freeme;

	if (!data->tokens)
		return (NULL);
	while (data->tokens)
	{
		freeme = data->tokens;
		safe_free(freeme->value);
		freeme->value = NULL;
		data->tokens = data->tokens->next;
		safe_free(freeme);
		freeme = NULL;
	}
	return (NULL);
}
