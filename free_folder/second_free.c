/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:39:22 by macampos          #+#    #+#             */
/*   Updated: 2023/12/06 19:40:13 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_push_swap.h"

int	second_free(t_stack *first_a, char **str, int x)
{
	if (!first_a)
	{
		while (str[x])
		{
			free(str[x]);
			x++;
		}
		return (0);
	}
	else
		return (1);
}
