# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/21 16:29:44 by sadolph           #+#    #+#              #
#    Updated: 2020/11/21 16:56:58 by sadolph          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile
CC := gcc
CFLAGS := -Wall -Wextra -Werror

# Directories
SRC_DIR := ./src/
#OBJ_DIR := ./obj/
LIBFT_DIR := ./libft/

INC_DIR := ./includes/
INC_HERE := minishell.h
LINK_INC := $(addprefix -I, $(INC_DIR) $(LIBFT_DIR)includes/)
LINK_LIB := -L$(LIBFT_DIR) -lft
LIBFT_NAME := libft.a

# Sources
NAME := minishell
SRC :=			\
parse.c			\
utils.c

# Objects
#OBJ := ${SRC:.c=.o}
#O_WITH_DIR := $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

# Add printf's object files to the libftprintf.a (renamed libft.a)
# Now, it's complete collection of all necessary functions into libftprintf.a
$(NAME): $(LIBFT_NAME) $(INC_DIR)$(INC_HERE)
	$(CC) $(CFLAGS) -o $(NAME) $(LINK_INC) $(LINK_LIB) $(SRC)

# Dependencies that allow recompile obj files from only changed source files
#$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)$(INC_PRINTF)
#	@mkdir -p $(OBJ_DIR)
#	$(CC) $(CFLAGS) $(LINK_INC) -c $< -o $@

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
