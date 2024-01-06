/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:00:04 by macampos          #+#    #+#             */
/*   Updated: 2024/01/06 18:00:18 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	thisthing(t_stack *current)
{
	int	len;

	len = 0;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}

double	thatthing(t_stack *current)
{
	double	sum;

	sum = 0;
	while (current != NULL)
	{
		sum += (current->content);
		current = current->next;
	}
	return (sum);
}

void	first_push_b(t_stack **stack_a, t_stack **stack_b)
{
	int				len;
	double			sum;
	int				average;

	len = thisthing(*stack_a);
	while (len > 3)
	{
		sum = thatthing(*stack_a);
		average = (sum / len);
		if ((*stack_a)->content < average)
			pushb(stack_a, stack_b);
		else
		{
			rotatea(stack_a);
		}
		len = thisthing(*stack_a);
	}
}

void	sort_low(t_stack **stack_a, t_stack **stack_b)
{
	int	len;

	len = thisthing(*stack_a);
	if (len == 5)
		sort5(stack_a, stack_b);
	if (len == 3)
		sort3(stack_a);
	if (len == 2)
		sort2(stack_a);
}

void	sort(t_stack **stack_a, t_stack **stack_b)
{
	int		len;

	len = thisthing(*stack_a);
	if (len == 2 || len == 3 || len == 5)
		sort_low(stack_a, stack_b);
	else if (len > 5 || len == 4)
	{
		first_push_b(stack_a, stack_b);
		sort3(stack_a);
		{
			while ((*stack_b) != NULL)
			{
				assign_bestfriend(stack_a, (*stack_b));
				assign_cost((*stack_a), stack_b);
				move_less_cost(stack_a, stack_b);
				move_stack_a(stack_a, stack_b, 0);
				pusha(stack_b, stack_a);
			}
		}
	}
	last_sort(stack_a);
}
