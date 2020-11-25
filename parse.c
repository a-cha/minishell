/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:28:51 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 12:25:38 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_linebreak(const char *line)
{
	size_t	res;
	size_t	s;

	res = ft_strlen(line);
	if ((s = is_symb(line, SEMICOLON)) < res)
		res = s;
	if ((s = is_symb(line, PIPE)) < res)
		res = s;
	return (res == ft_strlen(line) ? -1 : (int)res);
}

int			is_quotmark(const char *line)
{
	size_t	res;
	size_t	s;

	res = ft_strlen(line);
	if ((s = is_symb(line, '"')) < res)
		res = s;
	if ((s = is_symb(line, '\'')) < res)
		res = s;
	return (res == ft_strlen(line) ? -1 : (int)res);
}

size_t		catch_first_sign(const char *str, t_data *part, char *r)
{
	size_t	min;
	int		res;

	min = ft_strlen(str);
	if ((res = is_linebreak(str)) != -1 && res < min)
		min = res;
	if ((res = is_quotmark(str)) != -1 && res < min)
		min = res;
	if (str[min] == SEMICOLON)
		part->type = SEMICOLON;
	else if (str[min] == PIPE)
		part->type = PIPE;
	if (str[min] == '\'' || str[min] == '"')
		*r = str[min];
	else
		*r = '\0';
	return (min);
}

char 		*concatenate_env(char *dup, const char *line, size_t *s, t_data *part)
{
	char	*env;
	char	*tmp;
	size_t	f;

	f = 0;
	while ((line[f]) && ((ft_isalnum(line[f])) || line[f] == '_'))
		f++;
	if (!(env = ft_substr(line, 0, f)))
		return (NULL);
	tmp = env;
	if (!(env = find_env(&(part->env), env)))
		env = ft_strdup("");
	free_memory((void *)tmp);
	tmp = dup;
	if (!(dup = ft_strjoin(dup, env)))
		return (NULL);
	*s += f + 1;
	free_memory((void *)tmp);
	free_memory((void *)env);
	return (dup);
}

char		*handle_env(char *line, t_data *part)
{
	char 	*dup;
	char 	*dup1;
	char	*tmp;
	size_t	i;
	size_t	s;

	i = 0;
	dup = ft_strdup("");
	while (1)
	{
		s = is_symb(line + i, '$');
		dup1 = ft_substr(line, i, s == -1 ? ft_strlen(line + i) : s);
		tmp = dup;
		dup = ft_strjoin(dup, dup1);
		free_memory((void *)tmp);
		free_memory((void *)dup1);
		if (s == -1)
			break ;
		dup = concatenate_env(dup, line + i + s + 1, &s, part);
		i += s;
	}
	return (dup);
}

char		*handle_quot(char *line, t_data *part)
{
	char 	*dup;

	dup = handle_env(line, part);
	escape_symb_quot(dup);
//	MAYBE THIS FREE ISN'T NEEDED
//	free_memory((void *)line);
//		*************
	printf("quot: %s\n", dup);
//		*************
	return (dup);
}

// NEED TO TEST
// line before quotations (and without quots, except escaped)
char		**handle_line(char *line, t_data *part)
{
	char 	*dup;

	dup = handle_env(line, part);
	escape_symb_line(dup);
//	redirections(dup);
//	MAYBE THIS FREE ISN'T NEEDED
//	free_memory((void *)line);
//	split???
//		*************
	printf("line: %s\n", dup);
//		*************
	return (ft_split_pro(dup, ' '));
}

int			is_closed_quot(const char *line, char r)
{
	char	*tmp;
	int 	f;

	f = -2;
	if (r == '\'')
	{
		if ((tmp = ft_strchr(line, r)))
			f = (int)(tmp - line);
		else
			return (-1);
	}
	else if (r == '"')
		if ((f = is_symb(line, r)) == -1)
			return (-1);
	return (f);
}

int 		is_concat_args(char **args, char *quot, char t)
{
	char 	*tmp;
	char 	**tmp_d;
	size_t	f;

	if (t == ' ')
	{
		f = ft_arraylen(args);
		tmp = args[f];
		if (!(args[f] = ft_strjoin(args[f], quot)))
			return (-1);
		free_memory(tmp);
	}
	else
	{
		if (!(tmp_d = (char **)malloc(sizeof(char **))))
			return (-1);
		tmp_d = &quot;
		if (!(args = ft_arrjoin(args, tmp_d)))
			return (-1);
	}
	free_memory(quot);
	return (0);
}

//	returns the part of str until redir symbol (include redir symbol)
size_t		get_part(const char *line, t_data *part)
{
	size_t	i;
	int		f;
	size_t	s;
	char	*quot;
//	i can do without this variable (but this is just one string)
	char	r;

	i = 0;
	while (1)
	{
		s = catch_first_sign(line + i, part, &r);
		if (!(part->args = ft_arrjoin(part->args, handle_line(ft_substr(line, i, s), part))))
//			need to determine what to return
			return(errors(ERR_MALLOC, 5));
//		*************
		int t = -1;
		printf("\n");
		while (part->args[++t])
			printf(">%s<\n", part->args[t]);
//		*************
		if (r != '"' && r != '\'')
			break ;
		if ((f = is_closed_quot(line + i + 1, r)) < 0)
//			need to determine what to return
			return(errors(ERR_QUOTS, 5));
		if (!(quot = (r == '\'' ? ft_substr(line, i + s + 1, f) :
				handle_quot(ft_substr(line, i + s + 1, f - 1), part))))
			return(errors(ERR_MALLOC, 5));
		i += s + f + 3;
		if ((is_concat_args(part->args, quot, *(line + i + s - 1))))
			return(errors(ERR_MALLOC, 5));
//		*************
		t = -1;
		printf("\n");
		while (part->args[++t])
			printf(">%s<\n", part->args[t]);
//		*************
	}
//		*************
	int t = -1;
	printf("\n");
	while (part->args[++t])
		printf(">%s<\n", part->args[t]);
//		*************
	return (i + s + (part->type) ? 1 : 0);
}

t_data		*parse(const char *line, char **env)
{
	t_data	*part;
	int 	i;

//	MALLOC HERE
	part = ft_calloc(1, sizeof(t_data));
	part->args = (char **)malloc(sizeof(char **));
	part->args[0] = NULL;
	part->env = dup_env(env);
/*
//	save original fd
	part->input = dup(0);
	part->output = dup(1);
//	open file here
	part->outfile = open();
	dup2(part->outfile, 1);
//	open another here
	part->outfile = open();
	dup2(part->outfile, 1); // or 1 as a second argument
//	return the original fd
	dup2(part->output, 1);
*/
	while (*line)
	{
		i = get_part(line, part);
		part->len = ft_arraylen(part->args);
		line += i;
//		check weird cases (ls ;; ...)
//		call here processing functions
	}
	return (part);
}
