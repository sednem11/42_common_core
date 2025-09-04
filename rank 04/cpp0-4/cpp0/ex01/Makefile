NAME = PhoneBook
CFLAGS = -Wall -Werror -Wextra -std=c++98
CC = g++
RM = rm -rf
SRC = contact.cpp main.cpp PhoneBook.cpp
OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all