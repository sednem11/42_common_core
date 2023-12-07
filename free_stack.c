/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:59:09 by macampos          #+#    #+#             */
/*   Updated: 2023/12/06 18:59:13 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	free_stack(t_stack **stack_a)
{
	t_stack		*current;

	while ((*stack_a) != NULL)
	{
		current = (*stack_a)->next;
		free ((*stack_a));
		(*stack_a) = current;
	}
}
