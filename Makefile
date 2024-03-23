C_FILES = $(wildcard ./*.c)
O_FILES = $(C_FILES:%.c=build/%.o)
C_FLAGS = -Wall -Werror -Wextra
NAME = philo

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	$(CC) -O2 $^ -o $(NAME)

%.o: %.c 
	$(CC)  -O2 -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

fclean: clean
	-rm -f $(NAME)

re: fclean all
