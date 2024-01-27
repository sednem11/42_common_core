# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/27 18:38:34 by macampos          #+#    #+#              #
#    Updated: 2024/01/27 18:46:52 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name = so_long

SRCS =

OBJS = $(SRCS.o:=.o)

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

re:		fclean all