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
# include <string.h>

extern int			g_last_pid;
extern int			g_last_status;

typedef struct		s_env
{
	char			*env_name;
	char			*env_cont;
	char			is_equal;
}					t_env;

typedef struct		s_data
{
	char			**args;
	char			type;
	int				orig_input;
	int				orig_output;
	int				infile;
	int				outfile;
	int				pipe_fd[2];
	t_list			*env;
}					t_data;

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
int					is_quotmark(const char *line);
int					max(int n1, int n2);
int					space(const char *str, int start, int len);
int					ret_token(char t, int n, char *str);
int					set_status(int stat);
int 				free_and_exit(char *s1, char *s2, t_data *part, char flag);

/*
** Prototypes for commands
*/

t_data				*shell_init(int argc, char **argv, char **env);
int					process_status(void);
int					our_command(t_data *data);
int					our_command_if_no_pipe(t_data *data);
int					for_return(t_data *data, void (*f)(t_data *data));
void				child_process(t_data *data);
char				**list_to_array(t_data *data);
int					install_in_fd(t_data *data);
int					install_out_fd(t_data *data);
void				parent_process(t_data *data, int pid);
void				signal_oper(void);
void				pwd(t_data *data);
void				echo(t_data *data);
void				cd(t_data *data);
char				*find_env(t_list **env_dup, char *str);
t_env				*find_env1(t_list **env_dup, char *str);
void				remove_elem(t_list **env_dup, char *str);
int					is_first_symbol(const char *str, char c, int i);
char				*is_corr_path(char **arr, char *str);
void				env_export(t_data *data);
void				test_env_list(t_list **env_dup);
t_env				*env_to_cont(char *env);
void				ft_exit(t_data *data, int exit_status);
void				env_unset(t_data *data);
void				print_exp_list(t_list **env_dup);
t_env				*chek_env(t_data *data);
void				rewrite_cont(t_data *data, t_env *env);
void				print_error(char *er_status, char *er_mess, int new_line);

#endif
