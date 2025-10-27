NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes

# librerías para el enlace
LDLIBS  = -lreadline

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
	src/parser/expander_word.c \
    src/parser/expander.c \
    src/parser/parser.c \
    src/parser/parser_utils.c \
    src/parser/quotes.c \
    src/parser/tokenizer.c \
    src/parser/tokenizer_buf.c \
    src/parser/tokenizer_word.c \
    src/parser/tokenizer_pipe.c \
    src/parser/tokenizer_utils.c


OBJS = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): header $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)
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

header:
	@echo
	@echo "$(MAGENTA)┌──────────────────────────────────────────────────────────────────────────────┐$(RESET)"
	@echo "$(MAGENTA)│$(RESET)                           $(BLUE)★  42 Project  ★$(RESET)                                   $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)                                                                              $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)        $(CYAN)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗      $(RESET)  $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)        $(CYAN)████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║      $(RESET)  $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)        $(CYAN)██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║      $(RESET)  $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)        $(CYAN)██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║      $(RESET)  $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)        $(CYAN)██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ $(RESET)  $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)        $(CYAN)╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ $(RESET)  $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)                                                                              $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)                $(GREEN)<<<   M  I  N  I  S  H  E  L  L   >>>$(RESET)                         $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)│$(RESET)                     $(BLUE)by eldiaz-c $(WHITE)&$(BLUE) joperez2$(RESET)                                   $(MAGENTA)│$(RESET)"
	@echo "$(MAGENTA)└──────────────────────────────────────────────────────────────────────────────┘$(RESET)"
	@echo


.PHONY: all clean fclean re norminette header
