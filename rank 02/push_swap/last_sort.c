/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:59:42 by macampos          #+#    #+#             */
/*   Updated: 2023/12/06 19:01:00 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	go_down(t_stack **stack_a, t_stack *current)
{
	while ((*stack_a) != current)
		revrotatea(stack_a);
}

t_stack	*find_small(t_stack *stack_a)
{
	t_stack	*current;

	current = stack_a;
	while (stack_a != NULL)
	{
		if (current->content > stack_a->content)
			current = stack_a;
		stack_a = stack_a->next;
	}
	return (current);
}

void	last_sort(t_stack **stack_a)
{
	t_stack	*current;
	int		i;
	int		n;

	i = 0;
	n = 0;
	current = (*stack_a);
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	current = (*stack_a);
	while (current != find_small(*stack_a))
	{
		current = current->next;
		n++;
	}
	if (n < i / 2)
	{
		while ((*stack_a) != current)
			rotatea(stack_a);
	}
	else
		go_down(stack_a, current);
}
