/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bestfriendsort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:11:17 by macampos          #+#    #+#             */
/*   Updated: 2023/12/06 19:23:15 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

t_stack	*find_bestfriend(t_stack **stack_a, t_stack *stack_b1)
{
	t_stack	*current;
	t_stack	*current2;

	current = (*stack_a);
	while (current != NULL)
	{
		if (current->content > stack_b1->content)
		{
			current2 = current;
			while (current2 != NULL)
			{
				if (current->content > current2->content && 
					current2->content > stack_b1->content)
					current = current2;
				current2 = current2->next;
			}
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}
