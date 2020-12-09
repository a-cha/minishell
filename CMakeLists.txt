cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)
add_definitions( "-Wall -Wextra -Werror" )
include_directories(includes)
include_directories(libft/includes)

link_directories(libft)

add_executable(minishell
        includes/minishell.h
        libft/includes/get_next_line.h
        libft/includes/libasm.h
        libft/includes/libft.h
        libft/src/gnl/get_next_line.c
        libft/src/gnl/get_next_line_utils.c
        libft/src/libft/ft_atof.c
        libft/src/libft/ft_atoi.c
        libft/src/libft/ft_bzero.c
        libft/src/libft/ft_calloc.c
        libft/src/libft/ft_isalnum.c
        libft/src/libft/ft_isalpha.c
        libft/src/libft/ft_isascii.c
        libft/src/libft/ft_isdigit.c
        libft/src/libft/ft_isprint.c
        libft/src/libft/ft_itoa.c
        libft/src/libft/ft_lstadd_back.c
        libft/src/libft/ft_lstadd_front.c
        libft/src/libft/ft_lstclear.c
        libft/src/libft/ft_lstdelone.c
        libft/src/libft/ft_lstiter.c
        libft/src/libft/ft_lstlast.c
        libft/src/libft/ft_lstmap.c
        libft/src/libft/ft_lstnew.c
        libft/src/libft/ft_lstsize.c
        libft/src/libft/ft_memccpy.c
        libft/src/libft/ft_memchr.c
        libft/src/libft/ft_memcmp.c
        libft/src/libft/ft_memcpy.c
        libft/src/libft/ft_memmove.c
        libft/src/libft/ft_memset.c
        libft/src/libft/ft_numlens.c
        libft/src/libft/ft_putchar_fd.c
        libft/src/libft/ft_putendl_fd.c
        libft/src/libft/ft_putnbrs_fd.c
        libft/src/libft/ft_putstr_fd.c
        libft/src/libft/ft_split.c
        libft/src/libft/ft_strchr.c
        libft/src/libft/ft_strjoin.c
        libft/src/libft/ft_strlcat.c
        libft/src/libft/ft_strlcpy.c
        libft/src/libft/ft_strmapi.c
        libft/src/libft/ft_strncmp.c
        libft/src/libft/ft_strnstr.c
        libft/src/libft/ft_strrchr.c
        libft/src/libft/ft_strtrim.c
        libft/src/libft/ft_substr.c
        libft/src/libft/ft_tolower.c
        libft/src/libft/ft_toupper.c
        src/parse/arrays.c
        src/parse/env_subst.c
        src/parse/lines_and_quoters.c
        src/parse/parse.c
        src/parse/symbols.c
        src/parse/utils_parse.c
        src/parse/weird_cases.c
        src/process/cd.c
        src/process/common_utils.c
        src/process/echo.c
        src/process/env_export.c
        src/process/env_utils.c
        src/process/execve.c
        src/process/exit.c
        src/process/pwd.c
        src/process/signals.c
        src/process/unset.c
        src/parse/utils.c
        src/main.c
        src/parse/redirections.c
        src/process/processing_pipe.c
        src/parse/env_subst.c
        src/parse/lines_and_quoters.c
        src/parse/utils_weird_cases.c
        src/process/fd_utils.c)

target_link_libraries(minishell libft.a)
