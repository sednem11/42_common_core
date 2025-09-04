/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:39:17 by macampos          #+#    #+#             */
/*   Updated: 2023/12/06 19:40:10 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"

int	first_free(t_stack *first_a, char **str, t_stack **stack_a)
{
	if (!first_a)
	{
		free(str);
		free_stack(stack_a);
		return (0);
	}
	else
		return (1);
}
