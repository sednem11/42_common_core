/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:11:48 by macampos          #+#    #+#             */
/*   Updated: 2023/12/06 19:24:03 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

t_stack	*less_cost(t_stack *stack_b)
{
	t_stack	*current;

	current = stack_b;
	while (stack_b != NULL)
	{
		if (current->cost > stack_b->cost)
			current = stack_b;
		stack_b = stack_b->next;
	}
	return (current);
}
