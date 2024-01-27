# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 10:39:42 by macampos          #+#    #+#              #
#    Updated: 2024/01/22 13:28:39 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Pipex

SRCS = pipex.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = cc

$(NAME): $(OBJS)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a -Llibft -lft

all: $(NAME)

clean:
		cd libft && make clean
		rm -rf $(OBJS)

fclean:	clean
		cd libft && make fclean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re