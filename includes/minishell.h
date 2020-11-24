/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:22:50 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 22:05:12 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <unistd.h>
// delete
#include <stdio.h>
#include <string.h>

typedef struct		s_env
{
	char 			*env_name;
	char 			*env_cont;
}					t_env;

typedef struct		s_data
{
	char			**args;		// First element - command (ECHO, CD etc.), further - arguments (may be flags)
//	maybe we don't need len?
	size_t			len;		// Len of args array
	char			type;		// Type of break. If presented
//	file descriptors for redirections (maybe there is another implementation)
	int				infile;
	int 			outfile;
	t_list			*env;
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
void				*apply_nothing(void *elem);
void				del_content(void *elem);
t_list				*list_dup_sort(t_list **env);
void				free_memory(void **memory);
int					is_symb(const char *line, char c);





/*
** Prototypes for commands
*/ 
void				pwd(t_data *data);
void				echo(t_data *data);
void				cd(t_data *data);
char				*find_env(t_list **env_dup, char *str);
t_list				*dub_env(char **env);

#endif
