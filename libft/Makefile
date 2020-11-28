# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/29 12:48:54 by sadolph           #+#    #+#              #
#    Updated: 2020/11/02 18:53:08 by sadolph          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile
CC := gcc
CC_ASM := nasm
FLAGS := -Wall -Wextra -Werror
FLAGS_ASM := -f macho64

# Directories
SRC_DIR := ./src/
OBJ_DIR := ./obj/
LIBFT_DIR := $(SRC_DIR)libft/
GNL_DIR := $(SRC_DIR)gnl/
ASM_DIR := $(SRC_DIR)libasm/

INC_DIR := ./includes/
INC_ASM := $(INC_DIR)libasm.h
INC_LIBFT := $(INC_DIR)libft.h $(INC_ASM)
INC_GNL := $(INC_DIR)get_next_line.h
LINK_INC := -I $(INC_DIR)

# Sources
NAME := libft.a
SRC :=				\
ft_atof.c			\
ft_atoi.c			\
ft_bzero.c			\
ft_calloc.c			\
ft_isalnum.c		\
ft_isalpha.c		\
ft_isascii.c		\
ft_isdigit.c		\
ft_isprint.c		\
ft_memccpy.c		\
ft_memchr.c			\
ft_memcmp.c			\
ft_memcpy.c			\
ft_memmove.c		\
ft_memset.c			\
ft_strchr.c			\
ft_strlcat.c		\
ft_strlcpy.c		\
ft_numlens.c		\
ft_strncmp.c		\
ft_strnstr.c		\
ft_strrchr.c		\
ft_tolower.c		\
ft_toupper.c		\
\
ft_itoa.c			\
ft_putchar_fd.c		\
ft_putendl_fd.c		\
ft_putnbrs_fd.c		\
ft_putstr_fd.c		\
ft_split.c			\
ft_strjoin.c		\
ft_strmapi.c		\
ft_strtrim.c		\
ft_substr.c			\
\
ft_lstadd_back.c	\
ft_lstadd_front.c	\
ft_lstclear.c		\
ft_lstdelone.c		\
ft_lstiter.c		\
ft_lstlast.c		\
ft_lstmap.c			\
ft_lstnew.c			\
ft_lstsize.c

SRC_GNL :=			\
get_next_line.c		\
get_next_line_utils.c

SRC_ASM :=			\
ft_read.s			\
ft_strcmp.s			\
ft_strcpy.s			\
ft_strdup.s			\
ft_strlen.s			\
ft_write.s

# Objects
OBJ_LIBFT := ${SRC:.c=.o}
OBJ_GNL := ${SRC_GNL:.c=.o}
OBJ_ASM := ${SRC_ASM:.s=.o}
O_WITH_DIR := $(addprefix $(OBJ_DIR), $(OBJ_LIBFT) $(OBJ_GNL) $(OBJ_ASM))


all: $(NAME)

$(NAME): $(O_WITH_DIR)
	ar rc $@ $(O_WITH_DIR)
	ranlib $@
	@echo "\033[32m$@ successfully created\033[0m" ✅

# Dependencies that allow recompile obj files from only changed source files
$(OBJ_DIR)%.o: $(LIBFT_DIR)%.c $(INC_LIBFT)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(LINK_INC) -c $< -o $@

# + Get next line
$(OBJ_DIR)%.o: $(GNL_DIR)%.c $(INC_GNL)
	$(CC) $(FLAGS) $(LINK_INC) -c $< -o $@

# + Assembler functions
$(OBJ_DIR)%.o: $(ASM_DIR)%.s $(INC_ASM)
	$(CC_ASM) $(FLAGS_ASM) $(LINK_INC) -s $< -o $@

# Standard rules
clean:
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
