/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:43:36 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:33:09 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	update_value(t_env *node, const char *new_value)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_value);
}

static void	insert_node(t_env **head, t_env *prev, t_env *new)
{
	if (!new)
		return ;
	if (!prev)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		new->next = prev->next;
		prev->next = new;
	}
}

void	set_env(t_env **head, const char *key, const char *new_value)
{
	t_env	*new_node;
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			update_value(current, new_value);
			return ;
		}
		prev = current;
		current = current->next;
	}
	new_node = create_node(key, new_value);
	insert_node(head, prev, new_node);
}
