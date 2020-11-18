#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
// delete
#include <stdio.h>
#include <string.h>

/*
** Defines for processing
*/
# define ECHO (1)
# define CD (2)
# define PWD (3)
# define EXPORT (4)
# define UNSET (5)
# define ENV (6)
# define EXIT (7)
// for test
# define LS (8)

/*
** Defines for parsing
*/
# define PIPE (9)
# define SEMIC (10)
# define REDIR_R (11)
# define REDIR_DR (12)
# define REDIR_L (13)

typedef struct		s_data
{
    char			command; // ECHO CD
    char			**args;
    size_t			len;
    char			type;
    struct s_data	*next;
    struct s_data	*prev;
}					t_data;

#endif
