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
# include <sys/stat.h>
# include <stdlib.h>
// delete
#include <stdio.h>
#include <string.h>

typedef struct		s_env
{
	char 			*env_name;
	char 			*env_cont;
	char 			is_equal;
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
void				ft_arrayfree(char **array);
size_t				ft_arraylen(char **array);
char				**ft_arrayjoin(char **array1, char **array2);
void				*apply_nothing(void *elem);
void				del_content(void *elem);
t_list				*list_dup_sort(t_list **env);
void				free_memory(void *memory);
int					is_symb(const char *line, char c);
void			 	escape_symbols(char *dup);
t_data				*parse(const char *line, char **env);
char				**ft_split_pro(char const *s, char c);
t_list				*dup_env(char **env);


/*
** Prototypes for commands
*/
void				pwd(t_data *data);
void				echo(t_data *data);
void				cd(t_data *data);
char				*find_env(t_list **env_dup, char *str);
t_env				*find_env1(t_list **env_dup, char *str);
t_list				*find_env2(t_list **env_dup, char *str);
void 				remove_elem(t_list **env_dup, char *str);
int					is_first_symbol(const char *str, char c);
char				*is_corr_path(char **arr, char *str);
void				env_export(t_data *data);
void       			test_env_list(t_list **env_dup);
void				extern_bin(t_data *data, char **env);
t_env				*env_to_cont(char *env);
void				ft_exit(t_data *data);
void				env_unset(t_data *data);
void       			print_exp_list(t_list **env_dup, t_data *data);
int					is_last_symbol(const char *str, char c);




#endif
