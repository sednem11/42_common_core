/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:43:17 by macampos          #+#    #+#             */
/*   Updated: 2025/03/08 21:17:58 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	cealing_texture(char ***texture, char **line)
{
	(*texture) = ft_split((*line), ',');
	(get()->texture->c) = (int *)ft_calloc(4, sizeof(int));
	while (++get()->i < 3)
	{
		if (ft_strlen3((*texture)[get()->i]) != -1
			|| ft_atoi((*texture)[get()->i]) > 255
			|| is_all_num((*texture)[get()->i]) != 0)
			get()->check3 = 1;
		get()->texture->c[get()->i] = ft_atoi((*texture)[get()->i]);
		get()->j += (int)ft_strlen((*texture)[get()->i] + 1);
		free((*texture)[get()->i]);
	}
}

void	help_create_map(char *temp, int fd, char *str, int j)
{
	temp = get_next_line(fd);
	str = ft_strtrim(temp, "\n ");
	while (check_start_map(str) != 0)
	{
		free(temp);
		free(str);
		temp = get_next_line(fd);
		str = ft_strtrim(temp, "\n ");
	}
	while (j < get()->map_y)
	{
		(get())->map[j] = ft_strtrim(temp, "\n");
		j++;
		free(temp);
		temp = get_next_line(fd);
	}
	get()->map[get()->map_y] = NULL;
	free(temp);
	free(str);
}

void	help_end(int i)
{
	if (get()->images)
	{
		while (get()->images[i] != NULL)
		{
			if (get()->images[i]->img)
				mlx_destroy_image(get()->mlx, get()->images[i]->img);
			free(get()->images[i]);
			i++;
		}
		free(get()->images);
	}
	if (get()->mlx)
	{
		if (get()->window)
			mlx_destroy_window(get()->mlx, get()->window);
		mlx_destroy_display(get()->mlx);
		free(get()->mlx);
	}
	if (get()->texture)
	{
		free(get()->texture->so);
		free(get()->texture->we);
		free(get()->texture);
	}
}

int	end_before(char *line)
{
	int	i;

	i = 0;
	if (line)
		free(line);
	if (get()->map)
	{
		while (i < get()->map_y)
		{
			free(get()->map[i]);
			i++;
		}
		free(get()->map);
	}
	if (get()->texture)
	{
		free(get()->texture->c);
		free(get()->texture->f);
		free(get()->texture->ea);
		free(get()->texture->no);
	}
	help_end(0);
	exit(1);
	return (1);
}

void	get_texture_help(char *line, int i, char *line2)
{
	char	*str;

	get()->j = 2;
	while (line[get()->j] && line[get()->j] == ' ')
		get()->j++;
	if (line[get()->j])
	{
		str = ft_strtrim(&line[get()->j], "\n");
		if (i == 0)
			get()->texture->no = ft_strdup(str);
		else if (i == 1)
			get()->texture->ea = ft_strdup(str);
		else if (i == 2)
			get()->texture->so = ft_strdup(str);
		else if (i == 3)
			get()->texture->we = ft_strdup(str);
		else
			get()->i = -1;
		free(str);
		if (i == 4)
			get_floor_cealing(&line[get()->j], 1, line2);
		else if (i == 5)
			get_floor_cealing(&line[get()->j], 2, line2);
	}
}
