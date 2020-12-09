# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 16:29:44 by sadolph           #+#    #+#              #
#    Updated: 2020/12/09 18:54:43 by sadolph          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile
CC := gcc
CFLAGS := -Wall -Wextra -Werror

# Directories
SRC_DIR := ./src/
SRC_SUBDIRS := parse/ process/
SRC_ALL_DIRS := $(addsuffix :, $(addprefix $(SRC_DIR), $(SRC_SUBDIRS)))
OBJ_DIR := ./obj/

INC_DIR := ./includes/
LIBFT_DIR := ./libft/
INC_HERE := minishell.h
LINK := $(addprefix -I, $(INC_DIR) $(LIBFT_DIR)includes/) -L$(LIBFT_DIR) -lft

# Sources
NAME := minishell
LIBFT_NAME := libft.a
PROJ_LIB := minishell.a
SRC :=					\
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

OBJ := ${SRC:.c=.o}
O_WITH_DIR := $(addprefix $(OBJ_DIR), $(OBJ))


all: $(LIBFT_NAME) $(NAME)

$(NAME): $(O_WITH_DIR) $(SRC_DIR)main.c
	$(CC) $(CFLAGS) -o $(NAME) $(LINK) $^

VPATH = $(SRC_ALL_DIRS)

$(OBJ_DIR)%.o: %.c $(INC_DIR)$(INC_HERE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LINK) -c $< -o $@

$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean	
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all clean fclean re
