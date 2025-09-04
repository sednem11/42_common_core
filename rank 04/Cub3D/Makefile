# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <mcamposmendes@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 13:05:50 by macampos          #+#    #+#              #
#    Updated: 2025/02/20 09:56:34 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

SRCS = main.c parsing/check_map.c mlx_handler/start.c mlx_handler/raycasting.c mlx_handler/utils.c mlx_handler/utils2.c mlx_handler/utils3.c \
		parsing/utils4.c parsing/utils5.c parsing/utils6.c 

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

LIBFLAGS = -lXext -lX11
LIB = minilibx-linux/libmlx_Linux.a

CC = cc

$(NAME): $(OBJS)
		$(MAKE) -C ./libft
		$(MAKE) -C ./minilibx-linux
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB) $(LIBFLAGS) ./libft/libft.a -Llibft -lft -lm

all: $(NAME)

clean:	
			cd libft && make clean
			rm -rf $(OBJS)

fclean:	clean
			cd libft && make fclean
			rm -rf $(NAME)

norm_fix: fclean
	python3 -m c_formatter_42 $(SRCS)
	norminette $(SRCS)

re:		fclean all

.PHONY: all clean fclean re 