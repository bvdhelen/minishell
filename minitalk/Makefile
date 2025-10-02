CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_SRV = src/server.c
SRC_CLI = src/client.c

OBJS_SRV = $(SRC_SRV:.c=.o)
OBJS_CLI = $(SRC_CLI:.c=.o)

# Rules
all: server client

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

server: $(OBJS_SRV) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SRV) -L$(LIBFT_DIR) -lft -o server

client: $(OBJS_CLI) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLI) -L$(LIBFT_DIR) -lft -o client

clean:
	rm -f $(OBJS_SRV) $(OBJS_CLI)

fclean: clean
	rm -f server client
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

PHONY: all clean fclean re client server