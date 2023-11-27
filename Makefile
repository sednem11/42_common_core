# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:26:12 by macampos          #+#    #+#              #
#    Updated: 2023/11/21 19:47:47 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRCS = src/stack.c src/stackb.c ft_push_swap.c ft_sort.c bestfriendsort.c bestfriend_cost.c assign_bestfriend.c assign_cost.c less_cost.c move_less_cost.c free_stack.c last_sort.c

OBJS	= $(SRCS:.c=.o)


CFLAGS = -Wall -Wextra -Werror

CC = cc

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a -Llibft -lft

all:	$(NAME)

clean:
		cd libft && make clean
		rm -rf $(OBJS)

fclean:		clean
		cd libft && make fclean
		rm -rf $(NAME)

re:		fclean 	all

.PHONY : all clean fclean re