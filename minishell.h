#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"

#define ECHO 1
#define CD 2
#define PWD 3
#define EXPORT 4
#define UNSET 5
#define ENV 6
#define EXIT 7
#define LS 8

typedef struct		s_data
{
    char			command; // ECHO CD
    char			**args;
    size_t			len;
    char			type;
    struct s_data	*next;
    struct s_data	*prev;
}					t_data;

char **ft_split(char *s, char c);

#endif