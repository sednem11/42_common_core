/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:48:24 by macampos          #+#    #+#             */
/*   Updated: 2024/01/27 19:20:33 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SO_LONG_H
#define	SO_LONG_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct	data
{
	int		map_y;
	int		map_x;
}	t_data;

void	map_size_y(int fd);

#endif