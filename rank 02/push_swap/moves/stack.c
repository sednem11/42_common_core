/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:29:33 by macampos          #+#    #+#             */
/*   Updated: 2023/12/27 11:17:49 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"

t_stack	*create_node(int content)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	pusha(t_stack **stack_b, t_stack **stack_a)
{
	t_stack	*temp;

	temp = (*stack_b)->next;
	(*stack_b)->next = *stack_a;
	*stack_a = *stack_b;
	*stack_b = temp;
	ft_printf("%s\n", "pa");
}

void	swapa(t_stack **stack_a)
{
	t_stack	*temp;
	t_stack	*temp2;

	temp = *stack_a;
	temp2 = (*stack_a)->next;
	*stack_a = (*stack_a)->next;
	*stack_a = (*stack_a)->next;
	temp->next = *stack_a;
	*stack_a = temp;
	temp2->next = *stack_a;
	*stack_a = temp2;
	ft_printf("%s\n", "sa");
}

void	rotatea(t_stack **stack_a)
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
	ft_printf("%s\n", "ra");
}

void	revrotatea(t_stack **stack_a)
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
	ft_printf("%s\n", "rra");
}
