/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:12:42 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:34:10 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	del_node(t_env **head, char *key, t_env **previous, t_env **current)
{
	while (*current != NULL)
	{
		if (strcmp((*current)->key, key) == 0)
		{
			free((*current)->value);
			(*current)->value = NULL;
			if (*previous == NULL)
			{
				*head = (*current)->next;
				free((*current)->key);
				free(*current);
			}
			else
			{
				(*previous)->next = (*current)->next;
				free((*current)->key);
				free(*current);
			}
			return ;
		}
		*previous = *current;
		*current = (*current)->next;
	}
}

void	compare_arg_env(t_env **head, char *key)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = *head;
	del_node(head, key, &previous, &current);
}

int	builtin_unset(char **args, t_com *com, t_config *data)
{
	if (!args[1])
		return (0);
	args++;
	while (*args)
	{
		compare_arg_env (&data->env, *args);
		free_char_array(com->envp);
		com->envp = tok_envp(data->env);
		args++;
	}
	return (0);
}
