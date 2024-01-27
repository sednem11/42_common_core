/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:47:13 by macampos          #+#    #+#             */
/*   Updated: 2024/01/27 19:38:19 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data *get(void)
{
	static t_data data;
	return(&data);
}

void	get_xy(int fd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while(1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break;
		get()->map_x = ft_strlen(temp);
		free(temp);
		i++;
	}
	get()->map_y = i;
}

// void	parsing(void)
// {
// 	//checar a proporcao de pce;
// 	//ver se o mapa e quadrado
// 	//ver se o mapa e .ber
// 	//ver se o mapa tem saida (floodfill)
// 	//se for verdade passa.
// }

int	main(int argc, char **argv)
{

	(void)argc;
	get_xy(open(argv[1], O_RDONLY));
	//save map();
	//parsing();
	
	//iniciar os componentes do mlx
	//funcao de printar o mapa no terminal
	//funcaos dos movimentos
	//funcoa de terminar o jogo
	//inicia a parte grafica e troca a funcao de printar o mapa pela do mlx
	

}