/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:22:50 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/18 21:38:24 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
// delete
#include <stdio.h>
#include <string.h>

typedef struct		s_data
{
	char			**args;		// First element - command (ECHO, CD etc.), second - flags (if presented). Flags format: "-abcde"
//	maybe we don't need len?
	size_t			len;		// Len of args array
	char			type;		// Type of redirection. If presented
//	file descriptors for redirections (maybe there is another implementation)
	int				infile;
	int 			outfile;
	struct s_data	*next;
	struct s_data	*prev;
}					t_data;

/*
** Defines for parsing
*/
# define PIPE (9)
# define SEMIC (10)
# define REDIR_R (11)
# define REDIR_DR (12)
# define REDIR_L (13)

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
** Prototypes for parsing
*/
char				**ft_arrayfree(void **array);
size_t				ft_arraylen(void **array);
void				**ft_arrayjoin(void **array1, void **array2);

#endif
