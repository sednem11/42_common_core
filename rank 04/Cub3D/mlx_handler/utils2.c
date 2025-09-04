/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:34:45 by macampos          #+#    #+#             */
/*   Updated: 2025/03/08 21:04:25 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	my_pixel_get(t_image *image, int x, int y, int i)
{
	int	offset;

	y += (i * WINDOW_HEIGHT / get()->map_y);
	x += (i * WINDOW_LENGTH / get()->map_x);
	offset = (image->line_len * y) + (x * (image->bits_per_pixel / 8));
	return (*(unsigned int *)(image->image_pixel + offset));
}

void	my_pixel_put(t_image **image, int x, int y, int color)
{
	int	offset;

	offset = ((*image)->line_len * y) + (x * ((*image)->bits_per_pixel / 8));
	*((unsigned int *)(offset + (*image)->image_pixel)) = color;
}

void	rendering(t_image **image, int positionx, int positiony, int i)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < WINDOW_HEIGHT2 / get()->map_y)
	{
		x = 0;
		while (x < WINDOW_LENGTH2 / get()->map_x)
		{
			color = my_pixel_get((*image), x, y, i);
			if (color != -16777216)
				my_pixel_put(&get()->images[3], x + (WINDOW_LENGTH2
						/ get()->map_x * positionx) + 20, y + (WINDOW_HEIGHT2
						/ get()->map_y * positiony) + 10, color);
			x++;
		}
		y++;
	}
}

void	rendering2(int positionx, int positiony)
{
	int		x;
	int		y;
	int		color;

	get()->pixelx = get()->realpx - positionx;
	get()->pixely = get()->realpy - positiony;
	x = ((WINDOW_LENGTH2 / get()->map_x * get()->pixelx) - (WINDOW_LENGTH2
				/ get()->map_x * 0.1));
	y = ((WINDOW_HEIGHT2 / get()->map_y * get()->pixely) - (WINDOW_HEIGHT2
				/ get()->map_y * 0.1));
	while (y++ < ((WINDOW_HEIGHT2 / get()->map_y * get()->pixely)
			+ (WINDOW_HEIGHT2 / get()->map_y * 0.1)))
	{
		x = ((WINDOW_LENGTH2 / get()->map_x * get()->pixelx) - (WINDOW_LENGTH2
					/ get()->map_x * 0.1));
		while (x < ((WINDOW_LENGTH2 / get()->map_x * get()->pixelx)
				+ (WINDOW_LENGTH2 / get()->map_x * 0.1)))
		{
			color = trgb(200, 0, 0);
			my_pixel_put(&get()->images[3], x + (WINDOW_LENGTH2 / get()->map_x
					* positionx) + 20, y + (WINDOW_HEIGHT2 / get()->map_y
					* positiony) + 10, color);
			x++;
		}
	}
}

void	rendering_map(void)
{
	raycasting();
	get()->y = 0;
	while (check_start_map(get()->map[get()->y]) != 0)
		get()->y++;
	while (get()->map[get()->y])
	{
		get()->x = 0;
		while (get()->map[get()->y][get()->x] != '\0')
		{
			if (get()->map[get()->y][get()->x] == '2'
				|| get()->map[get()->y][get()->x] == 'y'
				|| get()->map[get()->y][get()->x] == 'N'
				|| get()->map[get()->y][get()->x] == 'E'
				|| get()->map[get()->y][get()->x] == 'S'
				|| get()->map[get()->y][get()->x] == 'W')
			{
				rendering(&get()->images[0], get()->x, get()->y, 0);
				rendering2(get()->x, get()->y);
			}
			if (get()->map[get()->y][get()->x] == '1')
				rendering(&get()->images[1], get()->x, get()->y, 0);
			get()->x++;
		}
		get()->y++;
	}
}
