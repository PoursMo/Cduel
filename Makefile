CC = gcc
CFLAG = -Wall -Wextra -Werror
SRCS = *.c
NAME = duel
RM = rm -f

all: $(NAME)

$(NAME):
	$(CC) $(CFLAG) $(SRCS) -o $@

clean:
	$(RM) $(NAME)

re: clean all

run: re
	./$(NAME)