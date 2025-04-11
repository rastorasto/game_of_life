CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g
NAME = game_of_life

all: game_of_life

$(NAME): $(NAME).cpp
	$(CXX) $(CXXFLAGS) -o $(NAME) $(NAME).cpp

clean:
	rm -f $(NAME) field.txt

.PHONY: clean
