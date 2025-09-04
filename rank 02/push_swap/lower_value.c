/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lower_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:05:01 by macampos          #+#    #+#             */
/*   Updated: 2024/01/11 17:02:07 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

t_stack	*find_lowest(t_stack **stack_a)
{
	t_stack	*current;
	t_stack	*current2;

	current = (*stack_a);
	current2 = (*stack_a);
	while (current->next != NULL)
	{
		if (current->content > current->next->content)
			current2 = (current->next);
		current = current->next;
	}
	return (current2);
}
