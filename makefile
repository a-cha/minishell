SRC = 		minishell.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			ft_split.c

OBJS	=	$(SRC:.c=.o)

CC = gcc

RM	= rm -f

CFLAGS		= -O3 -Wall -Wextra -Werror -I.

NAME = minishell

HEADER = minishell.h

RM		=		rm -f

all		:		$(NAME)

$(NAME)	:	$(OBJS)
	gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean	:
	$(RM) $(OBJS)

fclean	:		clean
	$(RM) $(NAME)

re		:		fclean all

.PHONY:		all clean fclean re