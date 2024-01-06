/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_less_cost.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:11:59 by macampos          #+#    #+#             */
/*   Updated: 2024/01/06 17:01:07 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	move_down_a(t_stack **stack_a, t_stack *b1)
{
	while ((*stack_a) != find_bestfriend(stack_a, b1))
	{
		revrotatea(stack_a);
	}
}

void	move_down(t_stack **stack_b, t_stack *b1)
{
	while ((*stack_b) != b1)
	{
		revrotateb(stack_b);
	}
}

void	move_up(t_stack **stack_b, t_stack *b1)
{
	while ((*stack_b) != b1)
	{
		rotateb(stack_b);
	}
}
typedef struct s_struct
{
	int		i;
	int		n;
	t_stack	*current;
}			t_stupid;

int	move_stack_a(t_stack **stack_a, t_stack **stack_b, int z)
{
	t_stupid	stupid;

	stupid.current = (*stack_a);
	stupid.i = thisthing(stupid.current);
	stupid.n = location(stack_a, less_cost(*stack_b));
	if (stupid.n <= stupid.i / 2 && z == 1)
	{
		move_all(stack_a, stack_b, 1, less_cost(*stack_b));
		return (1);
	}
	else if (stupid.n > stupid.i / 2 && z == 2)
	{
		move_all(stack_a, stack_b, 2, less_cost(*stack_b));
		return (1);
	}
	else if (stupid.n <= stupid.i / 2 && z == 0)
	{
		while ((*stack_a) != find_bestfriend(stack_a, (*stack_b)))
			rotatea(stack_a);
		return (1);
	}
	else if ((stupid.n >= stupid.i / 2 && z == 0))
	{
		move_down_a(stack_a, (*stack_b));
		return (1);
	}
	else
		return (0);
}

void	move_less_cost(t_stack **stack_a, t_stack **stack_b)
{
	t_stupid	stupid;

	stupid.n = 0;
	stupid.i = 0;
	stupid.current = (*stack_b);
	while (stupid.current != NULL)
	{
		stupid.current = stupid.current->next;
		stupid.i++;
	}
	stupid.current = (*stack_b);
	while (stupid.current != less_cost((*stack_b)))
	{
		stupid.current = stupid.current->next;
		stupid.n++;
	}
	if (stupid.n < stupid.i / 2)
	{
		if (move_stack_a(stack_a, stack_b, 1) == 0)
			move_up(stack_b, less_cost((*stack_b)));
	}
	else if (move_stack_a(stack_a, stack_b, 2) == 0)
		move_down(stack_b, less_cost((*stack_b)));
}
