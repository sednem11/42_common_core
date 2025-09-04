NAME = Zombie
CFLAGS = -Wall -Werror -Wextra -std=c++98
CC = g++
RM = rm -rf
SRC = newZombie.cpp main.cpp randomChump.cpp Zombie.cpp
OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all