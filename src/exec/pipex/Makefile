# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 13:07:07 by eldiaz-c          #+#    #+#              #
#    Updated: 2025/07/24 13:07:07 by eldiaz-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del archivo de la biblioteca
NAME = pipex

# Compilador y banderas de compilación
CC = cc
FLAGS = -Wall -Werror -Wextra

# Rutas de bibliotecas auxiliares
LIBFT_DIR = libft/
FT_PRINTF_DIR = ft_printf/
GET_NEXT_LINE_DIR = get_next_line/

# Archivo de encabezado / Inclusión de las bibliotecas
# -L ./libft sirve para decirle donde buscar la biblioteca
# -lft = libft.a sirve para indicar que biblioteca enlazar
INCLUDE_LIBFT = -L ./libft -lft
INCLUDE_FT_PRINTF = -L ./ft_printf -lftprintf
INCLUDE_GET_NEXT_LINE = -L ./get_next_line -l:get_next_line.a

# Definir códigos de color
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

# Archivos fuente y archivos objeto
SRC =	main.c \
		pipex.c \
		utils.c \
		utils2.c \
		ft_split_with_quotes.c \

OBJ = $(SRC:.c=.o)

# Archivos fuente y archivos objeto BONUS
SRC_BONUS =	pipex.c \
			utils.c \
			utils2.c \
			main_bonus.c \
			pipex_bonus.c \
			heredoc_bonus.c \
			ft_split_with_quotes.c \

OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Regla para crear los archivos objeto (.o)
# -c indica que se debe commpilar el código sin enlazar (crear solo el .o)
# $< representa el archivo de entrada (el .c que se está compilando)
# -o $@ especifica el nombre del archivo de salida que se está generando
.c.o:
	$(CC) $(FLAGS) -c $< -o $@

# Regla para compilar pipex con libft, ft_printf y get_next_line
# -C sirve para cambiar UNA VEZ al directorio especificado antes de ejecutar el Makefile
$(NAME): header $(OBJ)
	@make -C $(LIBFT_DIR) --no-print-directory
	@make -C $(FT_PRINTF_DIR) --no-print-directory
	@make -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) \
		$(INCLUDE_LIBFT) \
		$(INCLUDE_FT_PRINTF) \
		$(INCLUDE_GET_NEXT_LINE)
	@echo
	@echo "$(GREEN)<<< pipex compiled >>>$(RESET)"
	@echo

# Regla principal que lo compila todo
all: $(NAME)

# Regla para compilar pipex bonus con libft, ft_printf y get_next_line
# -C sirve para cambiar UNA VEZ al directorio especificado antes de ejecutar el Makefile
bonus: header $(OBJ_BONUS)
	@make -C $(LIBFT_DIR) --no-print-directory
	@make -C $(FT_PRINTF_DIR) --no-print-directory
	@make -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME) \
		$(INCLUDE_LIBFT) \
		$(INCLUDE_FT_PRINTF) \
		$(INCLUDE_GET_NEXT_LINE)
	@echo
	@echo "$(GREEN)<<< pipex bonus compiled >>>$(RESET)"
	@echo

# Eliminar todos los archivos .o y .a
clean:
	@rm -f $(OBJ) $(OBJ_BONUS) */*.o
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) clean -C $(FT_PRINTF_DIR) --no-print-directory
	@$(MAKE) clean -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@echo
	@echo "$(CYAN)<<< CLEAN COMPLETE >>>$(RESET)"
	@echo

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) fclean -C $(FT_PRINTF_DIR) --no-print-directory
	@$(MAKE) fclean -C $(GET_NEXT_LINE_DIR) --no-print-directory
	@echo "$(BLUE)<<< FULL CLEAN COMPLETE >>>$(RESET)"
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
	@echo " $(GREY)                  _                      "
	@echo " $(GREY)           ____  (_)___  ___  _  __      "
	@echo " $(GREY)          / __ \/ / __ \/ _ \| |/_/      "
	@echo " $(GREY)         / /_/ / / /_/ /  __/>  <        "
	@echo " $(GREY)        / .___/_/ .___/\___/_/|_|     __ "
	@echo " $(GREY)    ___/_/_____/_/_  __  _____  _____/ /_"
	@echo " $(GREY)   / __ \/ ___/ __ \/ / / / _ \/ ___/ __/"
	@echo " $(GREY)  / /_/ / /  / /_/ / /_/ /  __/ /__/ /_  "
	@echo " $(GREY) / .___/_/   \____/\__, /\___/\___/\__/  "
	@echo " $(GREY)/_/               /____/                 "
	@echo " $(RESET) "
	@echo

# Indica que las siguientes reglas no son archivos reales
.PHONY: all clean fclean re	norminette header bonus