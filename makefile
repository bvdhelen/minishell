NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Iincludes/libft -Iincludes/ft_printf -Iincludes/get_next_line

# Librerías para el enlace
LDLIBS  = -lreadline

# Rutas de bibliotecas auxiliares
LIBFT_DIR = includes/libft
FT_PRINTF_DIR = includes/ft_printf
GET_NEXT_LINE_DIR = includes/get_next_line

# Archivo de encabezado / Inclusión de las bibliotecas
# -L ./libft sirve para decirle donde buscar la biblioteca
# -lft = libft.a sirve para indicar que biblioteca enlazar
INCLUDE_LIBFT = -L $(LIBFT_DIR) -lft
INCLUDE_FT_PRINTF = -L $(FT_PRINTF_DIR) -lftprintf
INCLUDE_GET_NEXT_LINE = -L $(GET_NEXT_LINE_DIR) -l:get_next_line.a

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
	src/error_exit.c \
	src/parser/expander_word.c \
    src/parser/expander.c \
    src/parser/parser.c \
	src/parser/parser_debug.c \
    src/parser/parser_utils.c \
    src/parser/quotes.c \
    src/parser/tokenizer.c \
    src/parser/tokenizer_buf.c \
    src/parser/tokenizer_word.c \
    src/parser/tokenizer_pipe.c \
    src/parser/tokenizer_utils.c \
	src/exec/exec_cmd.c \
	src/exec/exec_pipe.c \
	src/exec/exec_cmd_utils.c \


OBJS = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar minishell con libft, ft_printf y get_next_line
# -C sirve para cambiar UNA VEZ al directorio especificado antes de ejecutar el Makefile
$(NAME): header $(OBJS)
	@make -C $(LIBFT_DIR) --no-print-directory
	@make -C $(FT_PRINTF_DIR) --no-print-directory
	@make -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)\
		$(INCLUDE_LIBFT) \
		$(INCLUDE_FT_PRINTF) \
		$(INCLUDE_GET_NEXT_LINE)
	@echo
	@echo "$(GREEN)<<< minishell compiled >>>$(RESET)"
	@echo

all: $(NAME)

clean:
	@rm -f $(OBJS) */*.o
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) clean -C $(FT_PRINTF_DIR) --no-print-directory
	@$(MAKE) clean -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@echo
	@echo "$(CYAN)<<< clean complete >>>$(RESET)"
	@echo

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) fclean -C $(FT_PRINTF_DIR) --no-print-directory
	@$(MAKE) fclean -C $(GET_NEXT_LINE_DIR) --no-print-directory
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
