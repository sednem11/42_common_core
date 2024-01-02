/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:12:08 by macampos          #+#    #+#             */
/*   Updated: 2024/01/02 15:13:04 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"

void	revrotateball(t_stack **stack_b)
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
}

void	revrotateall(t_stack **stack_a, t_stack **stack_b)
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
	revrotateball(stack_b);
	ft_printf("%s\n", "rrr");
}

void	rotateaall(t_stack **stack_a)
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
void	rotateball(t_stack **stack_b)
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

void	rotateall(t_stack **stack_a, t_stack **stack_b)
{
	rotateaall(stack_a);
	rotateball(stack_b);
	ft_printf("%s\n", "rr");
}
