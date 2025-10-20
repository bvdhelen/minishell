
NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

# Códigos de color
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN =  \033[0;36m
WHITE = \033[0;37m
GREY = \033[0;90m
RESET = \033[0m

SRC = \
	src/main.c \
	src/parser/expander.c \
	src/parser/parser.c \
	src/parser/quotes.c \
	src/parser/tokenizer.c \
	# src/exec \

OBJS = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): header $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo
	@echo "$(GREEN)<<< minishell compiled >>>$(RESET)"
	@echo

all: $(NAME)

clean:
	@rm -f $(OBJS) */*.o
	@echo
	@echo "$(CYAN)<<< clean complete >>>$(RESET)"
	@echo

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)<<< full clean complete >>>$(RESET)"
	@echo

re: fclean all

norminette:
	@norminette || true
	@echo
	@echo "$(GREEN)<<< norminette check OK >>>$(RESET)"
	@echo

# ASCII Art
header:
	@echo
	@echo "$(GREY)           __    _ __                       __                  ";
	@echo "$(GREY)    ____  / /_  (_) /___  _________  ____  / /_  ___  __________";
	@echo "$(GREY)   / __ \/ __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/";
	@echo "$(GREY)  / /_/ / / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) ";
	@echo "$(GREY) / .___/_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  ";
	@echo "$(GREY)/_/        ____  _________  __  _/_/_  _____/ /_                ";
	@echo "$(GREY)          / __ \/ ___/ __ \/ / / / _ \/ ___/ __/                ";
	@echo "$(GREY)         / /_/ / /  / /_/ / /_/ /  __/ /__/ /_                  ";
	@echo "$(GREY)        / .___/_/   \____/\__, /\___/\___/\__/                  ";
	@echo "$(GREY)       /_/               /____/                                 ";
	@echo " $(RESET) "
	@echo

.PHONY: all clean fclean re norminette header
