/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:38:46 by macampos          #+#    #+#             */
/*   Updated: 2025/03/07 19:48:37 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	create_image_addr(t_image *image)
{
	image->image_pixel = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_len, &image->endian);
	if (!image->image_pixel)
	{
		ft_printf("image_pixel");
		end_before(NULL);
	}
}

void	create_image_ptr2(t_image **image, int i)
{
	if (i == 0)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->no,
				&(*image)->width, &(*image)->height);
	if (i == 1)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->so,
				&(*image)->width, &(*image)->height);
	if (i == 2)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->ea,
				&(*image)->width, &(*image)->height);
	if (i == 3)
		(*image)->img = mlx_xpm_file_to_image(get()->mlx, get()->texture->we,
				&(*image)->width, &(*image)->height);
	if (!(*image)->img)
	{
		ft_putstr_fd("Texture Path not existent\n", 2);
		end_before(NULL);
	}
	create_image_addr(*image);
}

void	create_image_ptr(t_image **image, int width, int height)
{
	(*image)->img = mlx_new_image(get()->mlx, width, height);
	if (!(*image)->img)
	{
		ft_printf("ERROR\n");
		end_before(NULL);
	}
	create_image_addr(*image);
}

void	create_solid_color_image(t_image **image, int color)
{
	int	x;
	int	y;
	int	*pixel_data;

	(*image)->img = mlx_new_image(get()->mlx, WINDOW_LENGTH / get()->map_x,
			WINDOW_HEIGHT / get()->map_y);
	(*image)->width = WINDOW_LENGTH / get()->map_x;
	(*image)->height = WINDOW_HEIGHT / get()->map_y;
	if (!(*image)->img)
	{
		printf("ERROR creating image\n");
		end_before(NULL);
	}
	create_image_addr(*image);
	pixel_data = (int *)(*image)->image_pixel;
	y = 0;
	while (y++ < (*image)->height)
	{
		x = 0;
		while (x < (*image)->width)
		{
			pixel_data[(y * ((*image)->line_len / 4)) + x] = color;
			x++;
		}
	}
}
