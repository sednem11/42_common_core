/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:12:15 by macampos          #+#    #+#             */
/*   Updated: 2023/11/18 16:56:19 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"

void	pushb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp;
	temp = (*stack_a)->next;
	(*stack_a)->next = *stack_b;
	*stack_b = *stack_a;
	*stack_a = temp;
	ft_printf("%s\n", "pb");
}

void	swapb(t_stack **stack_b)
{
	t_stack *temp;
	t_stack	*temp2;
	temp = *stack_b;// 1
	temp2 = (*stack_b)->next;// 2
	*stack_b = (*stack_b)->next;// 2 3 4
	*stack_b = (*stack_b)->next;// 3 4
	temp->next = *stack_b;
	*stack_b = temp;// 1 3 4
	temp2->next = *stack_b;
	*stack_b = temp2;// 2 1 3 4
	ft_printf("%s\n", "sb");
}

void	rotateb(t_stack **stack_b)
{
	t_stack	*temp;
	t_stack *current;
	current = (*stack_b);
	temp = (*stack_b);// 1
	(*stack_b) = (*stack_b)->next;// 2 3 4
	if ((*stack_b)->next == NULL)
		(*stack_b)->next = temp;// 2 3 4 1
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = temp;
	}
	temp->next = NULL;
	ft_printf("%s\n", "rb");
}

void	revrotateb(t_stack **stack_b)
{
	t_stack	*temp;
	t_stack	*current;
	current = (*stack_b);
	while (current->next->next != NULL)
	{
		current = current->next;
	}
	temp = current->next;
	current->next = NULL;
	temp->next = (*stack_b);
	*stack_b = temp;
	ft_printf("%s\n", "rrb");
}
