# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 16:29:44 by sadolph           #+#    #+#              #
#    Updated: 2020/11/23 22:12:17 by pcatrina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile
CC := gcc
CFLAGS := #-Wall -Wextra -Werror

# Directories
SRC_DIR := ./src/
LIBFT_DIR := ./libft/

INC_DIR := ./includes/
INC_HERE := minishell.h
LINK_INC := $(addprefix -I, $(INC_DIR) $(LIBFT_DIR)includes/)
LINK_LIB := -L$(LIBFT_DIR) -lft
LIBFT_NAME := libft.a

# Sources
NAME := minishell
SRC :=								\
srcs/cd.c							\
srcs/echo.c							\
srcs/env_utils.c					\
srcs/pwd.c							\
srcs/utils.c						\
srcs/execve.c						\
srcs/env_export.c					\
srcs/exit.c							\
srcs/unset.c						\
srcs/signals.c						\
srcs/common_utils.c					\
srcs/processing_pipe.c				\
srcs/parse/arrays.c					\
srcs/parse/env_subst.c				\
srcs/parse/lines_and_quoters.c		\
srcs/parse/parse.c					\
srcs/parse/symbols.c				\
srcs/parse/utils_parse.c			\
srcs/parse/weird_cases.c			\
srcs/parse/redirections.c			\
main.c								\
#tests/tests_parsing.c				\

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(INC_DIR)$(INC_HERE)
	$(CC) $(CFLAGS) -o $(NAME) $(LINK_INC) $(LINK_LIB) $(SRC)

$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
fclean: clean
	rm -f minishell
	make -C $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all clean fclean re add_libft
