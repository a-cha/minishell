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
CFLAGS := -Wall -Wextra -Werror
LINK_FLAGS := -lft -O2 #-g -fsanitize=address

# Directories
SRC_DIR := ./src/
SRC_SUBDIRS := parse/ process/
SRC_ALL_DIRS := $(addsuffix :, $(addprefix $(SRC_DIR), $(SRC_SUBDIRS)))
OBJ_DIR := ./obj/
INCS_DIR := ./includes/
LIBFT_DIR := ./libft/
LINK_DIRS := -I $(INCS_DIR) -L $(LIBFT_DIR)

# Files
NAME := minishell
PROJ_LIB := minishell.a
LIBFT_NAME := libft.a
SRCS :=					\
cd.c					\
echo.c					\
env_utils.c				\
pwd.c					\
utils.c					\
execve.c				\
fd_utils.c				\
env_export.c			\
exit.c					\
unset.c					\
signals.c				\
common_utils.c			\
processing_pipe.c		\
arrays.c				\
env_subst.c				\
lines_and_quoters.c		\
parse.c					\
symbols.c				\
utils_parse.c			\
weird_cases.c			\
utils_weird_cases.c		\
redirections.c			\
main.c					\

OBJS := ${SRCS:.c=.o}
O_WITH_DIR := $(addprefix $(OBJ_DIR), $(OBJS))

all: $(LIBFT_NAME) $(NAME)

# Add printf's object files to the libftprintf.a
# Now, it's complete collection of all necessary functions into libftprintf.a
$(NAME): $(PROJ_LIB) $(SRC_DIR)main.c
	$(CC) $(CFLAGS) -o $(NAME) $(LINK_DIRS) $(SRC_DIR)main.c $(PROJ_LIB) $(LINK_FLAGS)
	@echo "\033[32m$(NAME) successfully created\033[0m" ✅

# Make library from project's obj files
$(PROJ_LIB): $(O_WITH_DIR)
	ar rc $(PROJ_LIB) $^
	ranlib $(PROJ_LIB)

# This is all source's subdirectories
VPATH = $(SRC_ALL_DIRS)

# Dependencies that allow recompile obj files only from changed source files
$(OBJ_DIR)%.o: %.c $(INCS_DIR)minishell.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c $< -o $@

# Building libft.a by lib's own Makefile.
$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

# Standard rules separated for miniRT & libft:
clean_here:
	rm -rf $(OBJ_DIR)
	rm -f $(PROJ_LIB)
fclean_here: clean_here
	rm -f $(NAME)
re_here: fclean_here all
clean_lib:
	$(MAKE) -C $(LIBFT_DIR)/ clean
fclean_lib:
	$(MAKE) -C $(LIBFT_DIR)/ fclean
re_lib:
	$(MAKE) -C $(LIBFT_DIR)/ re

# Standard rules for the whole project:
clean: clean_here clean_lib
fclean: fclean_here fclean_lib
re: re_lib re_here

.PHONY: all clean_here clean_lib clean fclean_here \
fclean_lib fclean re_here re_lib re
