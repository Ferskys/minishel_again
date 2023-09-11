/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:51:42 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 18:26:56 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_line(t_config *data)
{
	char	*str;
	char	*tmp;

	tmp = print_prompt();
	str = readline(tmp);
	free(tmp);
	if (!str)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		data->state = EXIT;
		return (NULL);
	}
	else
	{
		if (*str)
		{
			add_history(str);
			return (str);
		}
		else
			free(str);
	}
	return (NULL);
}

void	prompt(void)
{
	t_config	*data;

	data = get_data();
	data->prompt = read_line(data);
	validate_prompt(data);
	if (data->state == PROMPT && data->prompt)
		free(data->prompt);
}
