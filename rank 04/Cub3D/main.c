/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:44:43 by macampos          #+#    #+#             */
/*   Updated: 2025/03/08 21:18:09 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_data	*get(void)
{
	static t_data	data;

	return (&data);
}

int	is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 10 && (str[i] > 57 || str[i] < 48))
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen3(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			j++;
		i++;
	}
	if (j > 0 || i > 3)
		return (j);
	return (-1);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || open(argv[1], O_RDONLY) == -1)
	{
		ft_putstr_fd("wrong input", 2);
		return (1);
	}
	parsing(argv[1], open(argv[1], O_RDONLY));
	mlx_start();
	return (0);
}
