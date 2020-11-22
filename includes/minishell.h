/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:22:50 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/22 20:04:12 by sadolph          ###   ########.fr       */
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
	char			**args;		// First element - command (ECHO, CD etc.), further - arguments (may be flags)
//	maybe we don't need len?
	size_t			len;		// Len of args array
	char			type;		// Type of break. If presented
//	file descriptors for redirections (maybe there is another implementation)
	int				infile;
	int 			outfile;
	char			**env;
	struct s_data	*next;
	struct s_data	*prev;
}					t_data;

/*
** Defines for parsing
*/
# define SEMICOLON (59)
# define PIPE (124)

/*
** Prototypes for parsing
*/
char				**ft_arrayfree(void **array);
size_t				ft_arraylen(void **array);
void				**ft_arrayjoin(void **array1, void **array2);

/*
** Prototypes for commands
*/ 
void				pwd(t_data *data);
void				echo(t_data *data);
char				*find_env(char **env, char *str);

#endif
