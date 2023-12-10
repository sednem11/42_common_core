/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:30:54 by macampos          #+#    #+#             */
/*   Updated: 2023/10/12 18:43:53 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(const char *c, long int *counter)
{
	if (!c)
		ft_putstr("(null)", counter);
	else
	{
		while (*c)
		{
			ft_putchar(*c, counter);
			c++;
		}
	}
}
