/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cost.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:11:03 by macampos          #+#    #+#             */
/*   Updated: 2023/12/06 19:38:38 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	assign_cost(t_stack *stack_a, t_stack **stack_b)
{
	t_stack	*current;

	current = *stack_b;
	while (current != NULL)
	{
		current->cost = bestfriend_moves(stack_a, *stack_b, current);
		current = current->next;
	}
}
