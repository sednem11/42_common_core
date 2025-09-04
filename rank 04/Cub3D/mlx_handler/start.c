/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:51:19 by macampos          #+#    #+#             */
/*   Updated: 2025/03/08 21:04:20 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_mlx_window_images(void)
{
	get()->i = 0;
	get()->window = mlx_new_window(get()->mlx, WINDOW_LENGTH, WINDOW_HEIGHT,
		"Cub_3D");
	get()->images = (t_image **)ft_calloc(8, sizeof(t_image *));
	while (get()->i < 7)
	{
		(get()->images[get()->i]) = (t_image *)calloc(1, sizeof(t_image));
		get()->images[get()->i]->img = NULL;
		get()->i++;
	}
	create_image_ptr2(&get()->images[0], 0);
	create_image_ptr2(&get()->images[1], 1);
	create_image_ptr(&get()->images[2], WINDOW_LENGTH, WINDOW_HEIGHT);
	create_image_ptr(&get()->images[3], WINDOW_LENGTH, WINDOW_HEIGHT);
	create_image_ptr2(&get()->images[4], 2);
	create_image_ptr2(&get()->images[5], 3);
}

void	help_change_player(void)
{
	if (get()->realpx < get()->px)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->px -= 1;
		get()->map[get()->py][get()->px] = 'y';
	}
	if (get()->realpy < get()->py)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->py -= 1;
		get()->map[get()->py][get()->px] = 'y';
	}
	if (get()->realpx > get()->px + 1)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->px += 1;
		get()->map[get()->py][get()->px] = 'y';
	}
	if (get()->realpy > get()->py + 1)
	{
		get()->map[get()->py][get()->px] = '2';
		get()->py += 1;
		get()->map[get()->py][get()->px] = 'y';
	}
}

void	change_player(int key)
{
	float	directionangle;

	if (key == 1)
		directionangle = get()->player_angle;
	if (key == 2)
		directionangle = get()->player_angle + 90;
	if (key == 3)
		directionangle = get()->player_angle + 180;
	if (key == 4)
		directionangle = get()->player_angle + 270;
	if (directionangle > 360)
		directionangle -= 360;
	if ((get()->map[get()->py - 1][get()->px] != '1' || get()->realpy - 0.1
		* sin(directionangle * (3.1415926 / 180)) > get()->py + 0.1)
		&& (get()->map[get()->py + 1][get()->px] != '1' || get()->realpy - 0.1
			* sin(directionangle * (3.1415926 / 180)) < get()->py + 0.9))
		get()->realpy -= 0.1 * sin(directionangle * (3.1415926 / 180));
	if ((get()->realpx + 0.1 * cos(directionangle * (3.1415926
					/ 180)) > get()->px + 0.1 || get()->map[get()->py][get()->px
			- 1] != '1') && (get()->realpx + 0.1 * cos(directionangle
				* (3.1415926 / 180)) < get()->px + 0.9
			|| get()->map[get()->py][get()->px + 1] != '1'))
		get()->realpx += 0.1 * cos(directionangle * (3.1415926 / 180));
	help_change_player();
}

int	handle_input(int keysym)
{
	if (keysym == XK_Escape)
		end_before(NULL);
	if (keysym == XK_w)
		change_player(1);
	if (keysym == XK_a)
		change_player(2);
	if (keysym == XK_s)
		change_player(3);
	if (keysym == XK_d)
		change_player(4);
	if (keysym == XK_Left)
		get()->player_angle += 2.5;
	if (keysym == XK_Right)
		get()->player_angle -= 2.5;
	rendering_map();
	mlx_put_image_to_window(get()->mlx, get()->window, get()->images[3]->img, 0,
		0);
	return (1);
}

void	mlx_start(void)
{
	get()->mlx = mlx_init();
	init_mlx_window_images();
	rendering_map();
	mlx_put_image_to_window(get()->mlx, get()->window, get()->images[3]->img, 0,
		0);
	mlx_hook(get()->window, 2, (1L << 0), handle_input, NULL);
	mlx_hook(get()->window, 17, 0, end_before, NULL);
	mlx_loop(get()->mlx);
}
