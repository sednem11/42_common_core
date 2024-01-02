/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_errorok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:29:13 by macampos          #+#    #+#             */
/*   Updated: 2023/12/26 19:35:18 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	errorok(t_stack *stack_a)
{
	int	z;

	z = check_if_sorted(&stack_a);
	if (z == 1)
		ft_printf("%s\n", "Error");
	else if (z == 0)
		ft_printf("%s\n", "OK"); 
	free_stack(&stack_a);
}
