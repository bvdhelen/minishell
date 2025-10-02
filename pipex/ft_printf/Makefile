# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 19:57:16 by eldiaz-c          #+#    #+#              #
#    Updated: 2025/04/13 16:59:04 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del archivo de la biblioteca
NAME = libftprintf.a

# Compilador y banderas de compilacion
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Archivos fuente y archivos objeto
SOURCES = ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_putnbr_unsigned_fd.c \
		ft_putstr_fd.c \
		ft_print_hexadecimal_lower.c \
		ft_print_hexadecimal_upper.c \
		ft_print_pointer.c \
		ft_printf.c

OBJECTS = $(SOURCES:.c=.o)

# Archivo de encabezado
INCLUDE = ft_printf.h

# Crear bibliotecas y eliminar archivos
# AR = ar rcs crea, modifica y extrae archivos desde biblioteca, r remplaza, c crea, s indice
# RM = rm -f eliminar forzado

# Regla por defecto que lo compila todo
all: $(NAME)

# Regla para crear la biblioteca
$(NAME): $(OBJECTS) $(INCLUDE)
		@ar rcs $(NAME) $(OBJECTS)

# Regla para crear los archivos .o
$(OBJECTS):
		@$(CC) -c $(CFLAGS) $(SOURCES)

# Eliminar todos los archivos .o y .a
clean:
		@rm -f $(OBJECTS)

fclean: clean
		@rm -f $(NAME)

re: fclean $(NAME)

# Indica que las siguientes reglas no son archivos reales
.PHONY: all clean fclean re