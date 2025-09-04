/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:12:48 by macampos          #+#    #+#             */
/*   Updated: 2025/03/05 19:24:55 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	draw_vertical_line(int x, int height, int side)
{
	int	start;
	int	end;

	get()->y = 0;
	start = (WINDOW_HEIGHT / 2) - (height / 2);
	end = start + height;
	while (get()->y < start)
	{
		my_pixel_put(&get()->images[3], x, get()->y, trgb(get()->texture->c[0],
				get()->texture->c[1], get()->texture->c[2]));
		get()->y++;
	}
	get()->y = start;
	while (get()->y < end && get()->y < WINDOW_HEIGHT)
	{
		help_draw(get()->y, start, side, x);
		get()->y++;
	}
	get()->y = end;
	while (get()->y < WINDOW_HEIGHT)
	{
		my_pixel_put(&get()->images[3], x, get()->y, trgb(get()->texture->f[0],
				get()->texture->f[1], get()->texture->f[2]));
		get()->y++;
	}
}

void	help_dist(void)
{
	get()->calcx = get()->realpx;
	get()->calcy = get()->realpy;
	get()->ray_dx = cos((get()->ray_angle + 0.001) * (3.1415926 / 180));
	get()->ray_dy = sin((get()->ray_angle + 0.001) * (3.1415926 / 180));
	if (get()->ray_dx < 0)
		get()->step_x = -1;
	else
		get()->step_x = 1;
	if (get()->ray_dy < 0)
		get()->step_y = 1;
	else
		get()->step_y = -1;
	if (get()->step_x > 0)
		get()->side_distx = ((int)(get()->calcx + 1) - get()->calcx);
	else
		get()->side_distx = (get()->calcx - (int)get()->calcx);
	if (get()->step_y > 0)
		get()->side_disty = ((int)(get()->calcy + 1) - get()->calcy);
	else
		get()->side_disty = (get()->calcy - (int)get()->calcy);
	get()->dist_x = get()->side_distx / fabs(get()->ray_dx);
	get()->dist_y = get()->side_disty / fabs(get()->ray_dy);
}

float	cast_single_ray(void)
{
	help_dist();
	while (1)
	{
		if (get()->dist_x < get()->dist_y)
		{
			get()->calcx += get()->step_x;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				return (fabs(get()->dist_x));
			}
			get()->dist_x += fabs(1 / get()->ray_dx);
		}
		else
		{
			get()->calcy += get()->step_y;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				return (fabs(get()->dist_y));
			}
			get()->dist_y += fabs(1 / get()->ray_dy);
		}
	}
}

int	check_side(void)
{
	while (1)
	{
		if (get()->dist_x < get()->dist_y)
		{
			get()->calcx += get()->step_x;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				if (get()->ray_dx > 0)
					return (0);
				return (1);
			}
			get()->dist_x += fabs(1 / get()->ray_dx);
		}
		else
		{
			get()->calcy += get()->step_y;
			if (get()->map[(int)get()->calcy][(int)get()->calcx] == '1')
			{
				if (get()->ray_dy > 0)
					return (2);
				return (3);
			}
			get()->dist_y += fabs(1 / get()->ray_dy);
		}
	}
}

void	raycasting(void)
{
	get()->angle_increment = get()->fov / WINDOW_LENGTH;
	get()->x = 0;
	while (get()->x < WINDOW_LENGTH)
	{
		get()->ray_angle = get()->player_angle + (get()->fov / 2) - (get()->x
			* get()->angle_increment);
		if (get()->ray_angle < 0)
			get()->ray_angle += 360.0f;
		if (get()->ray_angle > 360.0f)
			get()->ray_angle -= 360.0f;
		get()->distance = cast_single_ray();
		if (get()->distance < 0.01f)
			get()->distance = 0.1f;
		get()->wallheight = (int)(WINDOW_HEIGHT / get()->distance);
		if (get()->wallheight > WINDOW_HEIGHT)
			get()->wallheight = WINDOW_HEIGHT;
		help_dist();
		draw_vertical_line(get()->x, get()->wallheight, check_side());
		get()->x++;
	}
}
