/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_no_dobles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:27:20 by macampos          #+#    #+#             */
/*   Updated: 2023/12/07 16:27:21 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	check_if_no_doubles(t_stack **stack_a)
{
	t_stack	*current;
	t_stack	*current2;

	current2 = (*stack_a);
	current = (*stack_a);
	while (current->next != NULL)
	{
		while (current2->next != NULL)
		{
			current2 = current2->next;
			if (current->content == current2->content)
			{
				free_stack(stack_a);
				return (1);
			}
		}
		current = current->next;
		current2 = current;
	}
	return (0);
}
