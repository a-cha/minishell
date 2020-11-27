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
# include <signal.h>
// delete
#include <stdio.h>
#include <string.h>

extern int				sigint_flag;
extern int				last_pid;
extern int				last_status;

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
	int				input;
	int 			output;
	int				infile;
	int 			outfile;
	t_list			*env;
	struct s_data	*next;
	struct s_data	*prev;
}					t_data;

/*
** Defines for erors
*/
# define ERR_QUOTS "Error quotation marks"
# define ERR_MALLOC "Malloc error"

int				 	errors(char *error, int err_code);

/*
** Defines for parsing
*/
# define SEMICOLON (59)
# define PIPE (124)

/*
** Prototypes for parsing
*/
void				ft_arrayfree(char **array);
int					ft_arraylen(char **array);
char				**ft_arrjoin_pro(char **array1, char **array2, char flag);
void				*apply_nothing(void *elem);
void				del_content(void *elem);
t_list				*list_dup_sort(t_list **env);
void				free_memory(void *memory);
int					is_symb(const char *line, char c);
void				escape_symb_line(char *dup);
void				escape_symb_quot(char *dup);
t_data				*parse(const char *line, char **env);
char				**ft_split_pro(char const *s, char c);
t_list				*dup_env(char **env);
void			 	print_d_array(char **array);


/*
** Prototypes for commands
*/
t_data 				*shell_init(int argc, char **argv, char **env);
t_data				*malloc_shell(char **env);
int 				process_status(void);
void				signal_oper();
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
void				ft_exit(t_data *data, int exit_status);
void				env_unset(t_data *data);
void       			print_exp_list(t_list **env_dup, t_data *data);
int					is_last_symbol(const char *str, char c);
t_env 				*chek_env(t_data *data);
void 				rewrite_cont(t_data *data, t_env *env);
void				*ctrl_c(t_data *data);
void				print_error(char *er_status, char *er_mess, int new_line);







#endif
