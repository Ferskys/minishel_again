/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 09:58:56 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/25 20:05:50 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	is_valid(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (exit(1));
}

int	main(int argc, char **argv)
{
	t_config	*data;	

	is_valid(argc, argv);
	data = get_data();
	data->state = INIT;
	while (1)
	{
		if (data->state == INIT)
			init();
		if (data->state == PROMPT)
			prompt();
		if (data->state == PARSE)
			parse();
		if (data->state == EXECUTE)
			execute();
		if (data->state == EXIT)
			exit_program();
	}
	return (0);
}
