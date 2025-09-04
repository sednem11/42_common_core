/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:49:53 by macampos          #+#    #+#             */
/*   Updated: 2025/03/08 21:13:29 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	check_map(char *name, int fd)
{
	int	i;

	(void)fd;
	i = 0;
	check_textures(open(name, O_RDONLY));
	while (name[i] && name[i] != '.')
		i++;
	if (strcmp(&name[i], ".cub") != 0)
		return (1);
	return (0);
}

void	get_floor_cealing(char *line, int i, char *line2)
{
	char	**texture;

	get()->j = 0;
	get()->check3 = 0;
	texture = NULL;
	if (i == 1)
	{
		texture = ft_split(line, ',');
		(get()->texture->f) = ft_calloc(4, sizeof(int));
		while (++get()->i < 3)
		{
			if (ft_strlen3(texture[get()->i]) != -1
				|| ft_atoi(texture[get()->i]) > 255
				|| is_all_num(texture[get()->i]) != 0)
				get()->check3 = 1;
			get()->texture->f[get()->i] = ft_atoi(texture[get()->i]);
			get()->j += (int)ft_strlen(texture[get()->i] + 1);
			free(texture[get()->i]);
		}
	}
	else if (i == 2)
		cealing_texture(&texture, &line);
	free(texture);
	if (get()->check3 == 1)
		end_before(line2);
}

void	get_textures(int fd)
{
	char	*line;

	line = get_next_line(fd);
	get()->texture = (t_textures *)ft_calloc(1, sizeof(t_textures));
	while (line != NULL)
	{
		get()->i = -1;
		while (get()->i < (int)ft_strlen(line) && get()->i++)
		{
			if (ft_strncmp(&line[get()->i], "NO ", 3) == 0)
				get_texture_help(&line[get()->i], 0, line);
			else if (ft_strncmp(&line[get()->i], "EA ", 3) == 0)
				get_texture_help(&line[get()->i], 1, line);
			else if (ft_strncmp(&line[get()->i], "SO ", 3) == 0)
				get_texture_help(&line[get()->i], 2, line);
			else if (ft_strncmp(&line[get()->i], "WE ", 3) == 0)
				get_texture_help(&line[get()->i], 3, line);
			else if (ft_strncmp(&line[get()->i], "F ", 2) == 0)
				get_texture_help(&line[get()->i], 4, line);
			else if (ft_strncmp(&line[get()->i], "C ", 2) == 0)
				get_texture_help(&line[get()->i], 5, line);
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	parsing(char *name, int fd)
{
	get()->j = 0;
	if (check_map(name, fd) == 1)
	{
		ft_putstr_fd("map is not acording to the needs", 2);
		end_before(NULL);
	}
	create_map(name);
	get_pxy(open(name, O_RDONLY));
	get_textures(open(name, O_RDONLY));
	floodfill(get()->map, get()->px, get()->py);
	while (get()->map[get()->j])
	{
		get()->i = 0;
		while (get()->map[get()->j][get()->i])
		{
			if (get()->map[get()->j][get()->i] == '0')
				floodfill(get()->map, get()->i, get()->j);
			get()->i++;
		}
		get()->j++;
	}
}
