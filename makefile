
SRC = 		minishell.c 

OBJS	=	$(SRC:.c=.o)

CC = gcc

RM	= rm -f

CFLAGS		= -O3 -I ./libft/# -Wall -Wextra -Werror 

LIBS = libft.a

NAME = minishell

HEADER = minishell.h

RM		=		rm -f

all		:		$(NAME)

$(NAME)	: make_lib	$(OBJS)
	gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} 

make_lib:
	make -C ./libft
	cp libft/libft.a ./

clean	:
	$(RM) $(OBJS)

fclean	:		clean
	$(RM) $(NAME)

re		:		fclean all

.PHONY:		all clean fclean re