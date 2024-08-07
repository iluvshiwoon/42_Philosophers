C_FILES = $(wildcard ./*.c)
C_FLAGS = -Wall -Werror -Wextra
NAME = philo

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	$(CC) -g $^ -o $(NAME)

build:
	mkdir -p build

clean:
	rm -rf build

fclean: clean
	-rm -f $(NAME)

re: fclean all
