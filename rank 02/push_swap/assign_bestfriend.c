/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_bestfriend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:10:56 by macampos          #+#    #+#             */
/*   Updated: 2024/01/10 17:23:32 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	assign_bestfriend(t_stack **stack_a, t_stack *stack_b)
{
	while (stack_b != NULL)
	{
		stack_b->bestfriend = find_bestfriend(stack_a, stack_b);
		stack_b = stack_b->next;
	}
}
