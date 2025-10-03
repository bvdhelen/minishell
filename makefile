CC      = cc
CFLAGS  = -Wall -Wextra -Werror

NAME    = philo

SRC = \
	src/main.c \
	src/parser/expacer.c src/parser/parser.c src/parser/quotes.c src_/parser/tokenizer.c \
	src/exec 

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
