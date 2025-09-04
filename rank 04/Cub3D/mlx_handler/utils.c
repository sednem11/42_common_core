/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:12:59 by macampos          #+#    #+#             */
/*   Updated: 2025/02/19 17:34:17 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	findx(t_image *image, int side)
{
	float	z;
	int		x;

	z = 0.0;
	if (get()->step_x > 0 && (side == 2 || side == 3))
		z = get()->realpx + get()->ray_dx * get()->distance;
	else if (get()->step_x < 0 && (side == 2 || side == 3))
		z = get()->realpx - fabs(get()->ray_dx * get()->distance);
	else if (get()->step_y < 0 && (side == 1 || side == 0))
		z = get()->realpy - get()->ray_dy * get()->distance;
	else if (get()->step_y > 0 && (side == 1 || side == 0))
		z = get()->realpy + fabs(get()->ray_dy * get()->distance);
	z = z - (int)z;
	x = z * image->width;
	return (x);
}

int	findy(t_image *image, int height, int y)
{
	float	z;
	int		x;

	z = (float)image->height / height;
	if (get()->distance < 1)
		y += ((WINDOW_HEIGHT / get()->distance - WINDOW_HEIGHT) / 2);
	x = (int)(y * z);
	return (x);
}

void	help_draw(int y, int start, int side, int x)
{
	if (side == 0)
	{
		my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[5],
				findx(get()->images[0], side), findy(get()->images[0],
					WINDOW_HEIGHT / get()->distance, y - start), 0));
	}
	else if (side == 1)
	{
		my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[4],
				findx(get()->images[0], side), findy(get()->images[0],
					WINDOW_HEIGHT / get()->distance, y - start), 0));
	}
	else if (side == 2)
	{
		my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[0],
				findx(get()->images[0], side), findy(get()->images[0],
					WINDOW_HEIGHT / get()->distance, y - start), 0));
	}
	else if (side == 3)
	{
		my_pixel_put(&get()->images[3], x, y, my_pixel_get(get()->images[1],
				findx(get()->images[5], side), findy(get()->images[0],
					WINDOW_HEIGHT / get()->distance, y - start), 0));
	}
}

int	trgb(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int	check_start_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (1);
		i++;
	}
	if (i > 0)
		return (0);
	return (1);
}
