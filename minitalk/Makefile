# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 12:51:05 by macampos          #+#    #+#              #
#    Updated: 2024/01/09 18:00:12 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

NAME2 = client

SRC = server.c

SRC2 = client.c server.c

OBJS = $(SRC:.c=.o)

OBJS2 = $(SRC2:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = cc

$(NAME): $(OBJS)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a -Llibft -lft
		
$(NAME2): $(OBJS2)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) -o $(NAME2) $(OBJS2) ./libft/libft.a -Llibft -lft

all:	$(NAME) $(NAME2)

clean:
		cd libft && make clean
		rm -rf $(OBJS)
		rm -rf $(OBJS2)

fclean:		clean
		cd libft && make fclean
		rm -rf $(NAME)
		rm -rf $(NAME2)
		
re:		fclean all

.PHONY:	all clean fclean re