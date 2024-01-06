/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_stack_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:19:21 by macampos          #+#    #+#             */
/*   Updated: 2024/01/06 18:27:18 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"

void	revrotateballbonus(t_stack **stack_b)
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
	current = (*stack_b);
}

void	revrotateallbonus(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp;
	t_stack	*current;

	current = (*stack_a);
	while (current->next->next != NULL)
	{
		current = current->next;
	}
	temp = current->next;
	current->next = NULL;
	temp->next = (*stack_a);
	*stack_a = temp;
	current = (*stack_a);
	revrotateballbonus(stack_b);
}

void	rotateaallbonus(t_stack **stack_a)
{
	t_stack	*temp;
	t_stack	*current;

	current = (*stack_a);
	temp = (*stack_a);
	(*stack_a) = (*stack_a)->next;
	if ((*stack_a)->next == NULL)
		(*stack_a)->next = temp;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = temp;
	}
	temp->next = NULL;
}

void	rotateballbonus(t_stack **stack_b)
{
	t_stack	*temp;
	t_stack	*current;

	current = (*stack_b);
	temp = (*stack_b);
	(*stack_b) = (*stack_b)->next;
	if ((*stack_b)->next == NULL)
		(*stack_b)->next = temp;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = temp;
	}
	temp->next = NULL;
}

void	rotateallbonus(t_stack **stack_a, t_stack **stack_b)
{
	rotateaall(stack_a);
	rotateball(stack_b);
}