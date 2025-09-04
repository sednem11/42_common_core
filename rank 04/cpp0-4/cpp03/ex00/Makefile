NAME = AnnnndOpen
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CXX = c++
RM = rm -rf
SRC = main.cpp ClapTrap.cpp
OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all