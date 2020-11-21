# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 16:29:44 by sadolph           #+#    #+#              #
#    Updated: 2020/11/21 19:39:36 by pcatrina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile
CC := gcc
CFLAGS := -Wall -Wextra -Werror

# Directories
SRC_DIR := ./srcs/
LIBFT_DIR := ./libft/

INC_DIR := ./includes/
INC_HERE := minishell.h
LINK_INC := $(addprefix -I, $(INC_DIR) $(LIBFT_DIR)includes/)
LINK_LIB := -L$(LIBFT_DIR) -lft
LIBFT_NAME := libft.a

# Sources
NAME := minishell
SRC := \
./srcs/main.c\
./srcs/pwd.c \
./srcs/echo.c\

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(INC_DIR)$(INC_HERE)
	$(CC) $(CFLAGS) -o $(NAME) $(LINK_INC) $(LINK_LIB) $(SRC)

$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

# Standard rules separated for ft_printf & libft:
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all clean fclean re add_libft