/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:42:08 by macampos          #+#    #+#             */
/*   Updated: 2025/03/07 19:48:37 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	get_pangle(char *line)
{
	get()->fov = 60;
	if (line[get()->i] == 'W')
		get()->player_angle = 180;
	else if (line[get()->i] == 'E')
		get()->player_angle = 0;
	else if (line[get()->i] == 'N')
		get()->player_angle = 90;
	else if (line[get()->i] == 'S')
		get()->player_angle = 270;
}

void	help_get_pxy(char **line, int fd)
{
	get()->check3 = 0;
	while ((*line) != NULL)
	{
		get()->i = -1;
		while (get()->i++ < (int)ft_strlen((*line)))
		{
			if ((*line)[get()->i] == 'E' || (*line)[get()->i] == 'W'
				|| (*line)[get()->i] == 'N' || (*line)[get()->i] == 'S')
			{
				get()->check3 += 1;
				get()->px = get()->i;
				get()->py = get()->j;
				get_pangle((*line));
			}
		}
		free((*line));
		(*line) = get_next_line(fd);
		get()->j++;
	}
}

void	get_pxy(int fd)
{
	char	*line;
	char	*str;

	line = get_next_line(fd);
	str = ft_strtrim(line, "\n ");
	while (check_start_map(str) != 0)
	{
		free(line);
		free(str);
		line = get_next_line(fd);
		str = ft_strtrim(line, "\n ");
	}
	help_get_pxy(&line, fd);
	get()->realpx = get()->px + 0.5;
	get()->realpy = get()->py + 0.5;
	free(line);
	free(str);
	if (get()->check3 != 1)
	{
		ft_putstr_fd("Map does not respect needs\n", 2);
		end_before(NULL);
	}
}

void	help_check_textures(char ***line)
{
	if ((*line)[0] != NULL && strcmp((*line)[0], "WE") == 0)
	{
		get()->check2 += 1;
		get()->check += 3;
	}
	else if ((*line)[0] != NULL && strcmp((*line)[0], "EA") == 0)
	{
		get()->check2 += 1;
		get()->check += 4;
	}
	else if ((*line)[0] != NULL && strcmp((*line)[0], "F") == 0)
	{
		get()->check2 += 1;
		get()->check += 5;
	}
	else if ((*line)[0] != NULL && strcmp((*line)[0], "C") == 0)
	{
		get()->check2 += 1;
		get()->check += 6;
	}
}

void	help_check_textures2(char ***line)
{
	get()->i = 0;
	if ((*line)[0] != NULL && strcmp((*line)[0], "NO") == 0)
	{
		get()->check2 += 1;
		get()->check += 1;
	}
	else if ((*line)[0] != NULL && strcmp((*line)[0], "SO") == 0)
	{
		get()->check2 += 1;
		get()->check += 2;
	}
	else
		help_check_textures(&(*line));
	while ((*line)[get()->i] != NULL)
	{
		free((*line)[get()->i]);
		get()->i++;
	}
	free((*line));
}
