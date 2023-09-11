/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:17:48 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 12:11:51 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_node(t_env **head, t_env **cur, t_env *new)
{
	if (new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
		(*cur)->next = new;
	*cur = new;
}

t_env	*create_node(const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

t_env	*create_env_list(char **env)
{
	t_env		*head;
	t_env		*current;
	char		**envp;
	char		*key;
	char		*value;

	head = NULL;
	current = NULL;
	envp = env;
	while (*envp)
	{
		key = strdup(*envp);
		value = ft_strchr(key, '=');
		if (value)
		{
			*value = '\0';
			value++;
			add_node(&head, &current, create_node(key, value));
			free(key);
		}
		envp++;
	}
	return (head);
}
