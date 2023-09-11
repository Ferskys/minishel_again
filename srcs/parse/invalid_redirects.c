/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 07:47:21 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 23:18:56 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_duplicate_fd(t_tokens **head)
{
    t_tokens *temp = *head;

    while (temp && temp->next)
    {
        if (temp->type == 6 && temp->next->type == 6)
        {
            // Save a reference to the node to be removed.
            t_tokens *node_to_remove = temp;

			// Re-link the nodes
			if (temp->prev != NULL)
				temp->prev->next = temp->next;
			else
				*head = temp->next;

			temp->next->prev = temp->prev;

			// Move temp pointer to next node
			temp = temp->next;

			// Free the node to be removed
			free(node_to_remove->value);
			free(node_to_remove);
		}
		else
			temp = temp->next;
    }
}

void remove_duplicate_outfile(t_tokens **head)
{
    t_tokens *temp = *head;

    while (temp && temp->next && temp->next->next)
    {
        if (temp->type == 5 && temp->next->type == 6 && temp->next->next->type == 5)
        {
            // Save references to the nodes to be removed.
            t_tokens *node_to_remove_1 = temp;
            t_tokens *node_to_remove_2 = temp->next;

            // Re-link the nodes
            if (temp->prev != NULL)
                temp->prev->next = temp->next->next;
            else
                *head = temp->next->next;

            temp->next->next->prev = temp->prev;

            // Move temp pointer to the node after the removed nodes
            temp = temp->next->next;

            // Free the nodes to be removed
            free(node_to_remove_1->value);
            free(node_to_remove_1);
            free(node_to_remove_2->value);
            free(node_to_remove_2);
        }
        else
            temp = temp->next;
    }
}

void checkAndSwapNodes(t_tokens **head_ref) {
    t_tokens *temp = *head_ref;
    while (temp != NULL && temp->next != NULL && temp->next->next != NULL) {
        if (temp->type == 5 && temp->next->type == 6 && temp->next->next->type == 3) {
            t_tokens *node5 = temp;
            t_tokens *node6 = temp->next;
            t_tokens *node3 = temp->next->next;
            t_tokens *nodeAfterNode3 = node3->next;

            // Re-link the nodes
            if (node5->prev != NULL)
                node5->prev->next = node3;
            else
                *head_ref = node3;

            node3->prev = node5->prev;
            node3->next = node5;
            node5->prev = node3;
            node5->next = node6;
            node6->prev = node5;
            node6->next = nodeAfterNode3;

            if (nodeAfterNode3 != NULL)
                nodeAfterNode3->prev = node6;

            // Move temp pointer to nodeAfterNode3
            temp = node5;
        }
		else
        	temp = temp->next;
    }
}
