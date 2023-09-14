/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 07:47:21 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/14 20:49:24 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_duplicate_fd(t_tokens **head)
{
	t_tokens	*temp;
	t_tokens	*node_to_remove;

	temp = *head;
	while (temp && temp->next)
	{
		if (temp->type == 6 && temp->next->type == 6)
		{
			node_to_remove = temp;
			if (temp->prev != NULL)
				temp->prev->next = temp->next;
			else
				*head = temp->next;
			temp->next->prev = temp->prev;
			temp = temp->next;
			free(node_to_remove->value);
			free(node_to_remove);
		}
		else
			temp = temp->next;
	}
}

static int	check_match(int node1, int node2, int node3)
{
	return (node1 == 5 && node2 == 6 && node3 == 5);
}

void	remove_duplicate_outfile(t_tokens **head)
{
	t_tokens	*temp;
	t_tokens	*node_to_remove_1;
	t_tokens	*node_to_remove_2;

	temp = *head;
	while (temp && temp->next && temp->next->next)
	{
		if (check_match(temp->type, temp->next->type, temp->next->next->type))
		{
			node_to_remove_1 = temp;
			node_to_remove_2 = temp->next;
			if (temp->prev != NULL)
				temp->prev->next = temp->next->next;
			else
				*head = temp->next->next;
			temp->next->next->prev = temp->prev;
			temp = temp->next->next;
			free(node_to_remove_1->value);
			free(node_to_remove_1);
			free(node_to_remove_2->value);
			free(node_to_remove_2);
		}
		else
			temp = temp->next;
	}
}

void	swap_nodes(t_swap_nodes *nodes, t_tokens **head_ref)
{
	t_tokens	*node5;
	t_tokens	*node6;
	t_tokens	*node3;
	t_tokens	*node_after_3;

	node5 = nodes->node5;
	node6 = nodes->node6;
	node3 = nodes->node3;
	node_after_3 = nodes->node_after_3;
	if (node5->prev != NULL)
		node5->prev->next = node3;
	else
		*head_ref = node3;
	node3->prev = node5->prev;
	node3->next = node5;
	node5->prev = node3;
	node5->next = node6;
	node6->prev = node5;
	node6->next = node_after_3;
	if (node_after_3 != NULL)
		node_after_3->prev = node6;
}

void	swap_tokens(t_tokens **head_ref)
{
	t_tokens		*temp;
	t_swap_nodes	nodes;

	temp = *head_ref;
	while (temp != NULL && temp->next != NULL && temp->next->next != NULL)
	{
		if (temp->type == 5 && temp->next->type == 6
			&& temp->next->next->type == 3)
		{
			nodes.node5 = temp;
			nodes.node6 = temp->next;
			nodes.node3 = temp->next->next;
			nodes.node_after_3 = nodes.node3->next;
			swap_nodes(&nodes, head_ref);
			temp = nodes.node5;
		}
		else
		{
			temp = temp->next;
		}
	}
}
