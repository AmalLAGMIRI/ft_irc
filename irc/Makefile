F_NAME = server.cpp client.cpp channel.cpp main.cpp command.cpp ft_bot.cpp ft_transfer_file.cpp

NAME = ircserv
CXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror -fsanitize=address -g3

O_FILE = $(F_NAME:.cpp=.o)

all: $(NAME)

$(NAME): $(O_FILE)
	$(CXX) $(CXXFLAGS) $(O_FILE) -o $(NAME)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -rf $(O_FILE)

fclean: clean
	rm -rf $(NAME)