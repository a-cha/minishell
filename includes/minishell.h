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
	int				orig_input;
	int 			orig_output;
	char			flag_redir;
	int				infile;
	int 			outfile;
	int				pipe_fd[2];
	t_list			*env;
}					t_data;

/*
** Defines for parsing
*/

# define SEMICOLON (59)
# define PIPE (124)

/*
** Prototypes for parsing
*/

size_t				catch_first_sign(const char *str, t_data *part, char *r);
int					parse(const char *line, t_data *part);
void				ft_arrayfree(char **array);
int					ft_arrlen(char **array);
char				**ft_arrjoin_pro(char **arr1, char **arr2, char flag);
void				*copy_t_env(void *elem);
void				del_content(void *elem);
t_list				*list_dup_sort(const t_data *data);
void				free_memory(void *memory);
int					is_symb(const char *line, char c);
t_list				*dup_env(char **env);
void				reset_t_data(t_data *data);
int					is_linebreak(const char *line);
int					weird_cases(const char *line);
char				*handle_env(char *line, t_data *part);
int					is_closed_quot(const char *line, char r);
char				**handle_line(const char *line, int s, int f, t_data *part);
char				*handle_quot(char *line, t_data *part);
void				redirections(char *line, t_data *part);
int					is_redir(const char *line, char *r);
int					set_redir(char *name, char flag, t_data *part);
int					is_quotmark(const char *line);
char		 		is_in_quots(const char *line, size_t n);
//	remove
void			 	print_d_array(char **array);

/*
** Prototypes for commands
*/

t_data 				*shell_init(int argc, char **argv, char **env);
t_data				*malloc_shell(char **env);
void				new_processing(t_data *data);
int 				process_status(void);
int 				our_command(t_data *data);
int 				our_command_if_no_pipe(t_data *data);
void				processing(t_data *data);
void				processing_pipe(t_data *data);
void				child_process(t_data *data);
char				**list_to_array(t_data *data);
int 				install_in_fd(t_data *data);
int					install_out_fd(t_data *data);
void				parent_process(t_data *data,int pid);
void				signal_oper(void);
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
void				extern_bin(t_data *data);
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
