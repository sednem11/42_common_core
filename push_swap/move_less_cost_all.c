/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_less_cost_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:27:03 by macampos          #+#    #+#             */
/*   Updated: 2024/01/06 18:04:40 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	move_down_all(t_stack **stack_a, t_stack **stack_b, t_stack *b1)
{
	while ((*stack_b) != b1 && (*stack_a) != find_bestfriend(stack_a, b1))
	{
		revrotateall(stack_a, stack_b);
	}
	while ((*stack_b) != b1)
	{
		revrotateb(stack_b);
	}
	
}

void	move_up_all(t_stack **stack_a, t_stack **stack_b, t_stack *b1)
{
	while ((*stack_b) != b1 && (*stack_a) != find_bestfriend(stack_a, b1))
	{
		rotateall(stack_a, stack_b);
	}
	while ((*stack_b) != b1)
	{
		rotateb(stack_b);
	}
}

int	move_all(t_stack **stack_a, t_stack **stack_b, int z, t_stack *b1)
{
	if (z == 2)
	{
		move_down_all(stack_a, stack_b, b1);
		return (1);
	}
	if (z == 1)
	{
		move_up_all(stack_a, stack_b, b1);
		return (1);
	}
	return (0);
}
