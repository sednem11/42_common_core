/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_sorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:33:22 by macampos          #+#    #+#             */
/*   Updated: 2023/12/26 19:36:17 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	check_if_sorted(t_stack **stack_a)
{
	t_stack	*current;

	current = (*stack_a);
	while (current->next != NULL)
	{
		if (current->content > (current->next)->content)
			return (1);
		current = current->next;
	}
	return (0);
}
