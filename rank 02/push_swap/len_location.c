/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_location.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:01:47 by macampos          #+#    #+#             */
/*   Updated: 2024/01/04 11:48:56 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	location(t_stack **stack_a, t_stack *stack_b)
{
	t_stack	*current;
	int		n;

	n = 0;
	current = (*stack_a);
	while (current != find_bestfriend(stack_a, stack_b))
	{
		current = current->next;
		n++;
	}
	return (n);
}
