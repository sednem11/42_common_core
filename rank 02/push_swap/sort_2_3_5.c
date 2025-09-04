/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2_3_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:38:56 by macampos          #+#    #+#             */
/*   Updated: 2024/01/11 16:58:30 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	sort3(t_stack **stack_a)
{
	if ((*stack_a)->content > ((*stack_a)->next)->content)
		swapa(stack_a);
	if (((*stack_a)->next)->content > (((*stack_a)->next)->next)->content)
	{
		if ((((*stack_a)->next)->next)->content > (*stack_a)->content)
		{
			revrotatea(stack_a);
			swapa(stack_a);
		}
		else
			revrotatea(stack_a);
	}
}

void	sort2(t_stack **stack_a)
{
	if ((*stack_a)->content > ((*stack_a)->next)->content)
		swapa(stack_a);
}

void	sort2_stack_b(t_stack **stack_b)
{
	if (((*stack_b)->next)->content > (*stack_b)->content)
		swapb(stack_b);
}

void	first_push_b_5(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*current;
	t_stack	*current2;
	t_stack	*current3;

	current2 = find_lowest(stack_a);
	current3 = (*stack_a);
	current = (*stack_a);
	while (current->next != NULL)
	{
		if (current->content > current->next->content
			&& current->next->content != current2->content)
			current3 = current->next;
		current = current->next;
	}
	while (thisthing(*stack_a) > 3)
	{
		if ((*stack_a)->content == current2->content
			|| (*stack_a)->content == current3->content)
			pushb(stack_a, stack_b);
		else
			rotatea(stack_a);
	}
}

void	sort5(t_stack **stack_a, t_stack **stack_b)
{
	first_push_b_5(stack_a, stack_b);
	sort3(stack_a);
	sort2_stack_b(stack_b);
	pusha(stack_b, stack_a);
	pusha(stack_b, stack_a);
}
