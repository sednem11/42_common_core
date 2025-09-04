# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 13:58:50 by yohan             #+#    #+#              #
#    Updated: 2025/05/28 14:50:01 by ycantin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
FLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++

SRC = 	main.cpp \
		source/security.cpp \
		source/server.cpp \
		source/client.cpp \
		source/.config.cpp \
		source/channel.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: clean all
