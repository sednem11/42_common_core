# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:26:12 by macampos          #+#    #+#              #
#    Updated: 2024/01/02 15:42:12 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

BONUS_NAME = checker

SRCS = moves/stack.c moves/stackb.c ft_push_swap.c ft_sort.c bestfriendsort.c bestfriend_cost.c assign_bestfriend.c check_if_no_dobles.c moves/both_stack.c  \
		assign_cost.c less_cost.c move_less_cost_all.c move_less_cost.c free_stack.c last_sort.c free_folder/first_free.c free_folder/second_free.c check_if_sorted.c  \

SRC_BONUS = bonus_moves/stack.c bonus_moves/stackb.c moves/both_stack.c checker.c free_folder/first_free.c free_folder/second_free.c free_stack.c check_if_no_dobles.c checker_errorok.c check_if_sorted.c  \

OBJS	= $(SRCS:.c=.o)

BONUS_OBJS	= $(SRC_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror#-fsanitize=address

CC = cc

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a -Llibft -lft
	
all:	$(NAME) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) ./libft/libft.a -Llibft -lft

bonus: $(BONUS_NAME)

clean:
		cd libft && make clean
		rm -rf $(OBJS)
		rm -rf $(BONUS_OBJS)

fclean:		clean
		cd libft && make fclean
		rm -rf $(NAME)
		rm -rf $(BONUS_NAME)

re:		fclean 	all
		fclean	bonus

.PHONY : all clean fclean re