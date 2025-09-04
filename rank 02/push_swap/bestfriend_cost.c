/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bestfriend_cost.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:11:09 by macampos          #+#    #+#             */
/*   Updated: 2024/01/06 16:44:21 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	bestfriend_moves_a(t_stack *stack_a, t_stack *node_b)
{
	int		i;
	int		j;
	t_stack	*current;

	current = stack_a;
	i = 0;
	j = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	current = stack_a;
	while (current != node_b->bestfriend)
	{
		current = current->next;
		j++;
	}
	if (j < i / 2)
		return (j);
	else
		return (i - j);
}

int	bestfriend_moves(t_stack *stack_a, t_stack *stack_b, t_stack *b1)
{
	int		i;
	int		n;
	int		j;
	t_stack	*current;

	current = stack_b;
	i = 0;
	n = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	current = stack_b;
	while (current != b1 && current != NULL)
	{
		current = current->next;
		n++;
	}
	j = bestfriend_moves_a(stack_a, b1);
	if (n <= i / 2)
		return (n + j);
	else
		return (i - n + j);
}
