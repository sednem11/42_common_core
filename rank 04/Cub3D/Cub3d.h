/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:42:28 by macampos          #+#    #+#             */
/*   Updated: 2025/03/10 10:10:28 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WINDOW_LENGTH2 200
# define WINDOW_HEIGHT2 150

# define WINDOW_LENGTH 800
# define WINDOW_HEIGHT 500

typedef struct s_image
{
	void	*img;
	char	*image_pixel;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}		t_image;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*c;
	int		*f;
}	t_textures;

typedef struct s_data
{
	int			map_y;
	int			map_x;
	int			i;
	int			y;
	int			x;
	int			j;
	int			px;
	int			py;
	float		calcx;
	float		calcy;
	float		realpy;
	float		realpx;
	float		fov;
	float		angle_increment;
	float		ray_angle;
	float		player_angle;
	float		distance;
	float		ray_dx;
	float		ray_dy;
	float		delta_distx;
	float		delta_disty;
	float		side_disty;
	float		side_distx;
	float		heightx;
	float		heighty;
	float		dist_x;
	float		dist_y;
	float		pixelx;
	float		pixely;
	int			step_x;
	int			step_y;
	int			wallheight;
	int			lastx;
	int			lasty;
	char		**map;
	t_textures	*texture;
	t_image		**images;
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	int			check;
	int			check2;
	int			check3;
}	t_data;

t_data	*get(void);

int		ft_strlen3(char *line);
void	parsing(char *name, int fd);
void	mlx_start(void);
int		check_start_map(char *line);
void	raycasting(void);
void	my_pixel_put(t_image **image, int x, int y, int color);
int		trgb(int red, int green, int blue);
int		my_pixel_get(t_image *image, int x, int y, int i);
int		end_before(char *line);
void	help_draw(int y, int start, int side, int x);
int		findy(t_image *image, int height, int y);
int		findx(t_image *image, int side);
int		my_pixel_get(t_image *image, int x, int y, int i);
void	my_pixel_put(t_image **image, int x, int y, int color);
void	rendering(t_image **image, int positionx, int positiony, int i);
void	rendering2(int positionx, int positiony);
void	rendering_map(void);
void	create_image_addr(t_image *image);
void	create_image_ptr2(t_image **image, int i);
void	create_image_ptr(t_image **image, int width, int height);
void	create_solid_color_image(t_image **image, int color);
void	get_pangle(char *line);
void	help_get_pxy(char **line, int fd);
void	get_pxy(int fd);
void	help_check_textures(char ***line);
void	help_check_textures2(char ***line);
void	cealing_texture(char ***texture, char **line);
void	help_create_map(char *temp, int fd, char *str, int j);
void	help_end(int i);
void	get_texture_help(char *line, int i, char *line2);
void	mapy(int fd);
void	mapx(int fd);
void	create_map(char *name);
void	floodfill(char **map, int x, int y);
void	check_textures(int fd);
void	get_floor_cealing(char *line, int i, char *line2);
int		is_all_num(char *str);

#endif