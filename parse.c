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

int		is_linebreak(const char *line)
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

int		is_quotmark(const char *line)
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

char 	*concatenate_env(char *dup, const char *line, size_t *s, t_data *part)
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

char	*handle_env(const char *line, t_data *part)
{
	char 	*dup;
	char 	*dup1;
	char	*tmp;
	size_t	i;
	size_t	s;

	i = 0;
	dup = ft_strdup("");
	while ((s = is_symb(line + i, '$')))
	{
		dup1 = ft_substr(line, i, s);
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

char	*handle_quot(const char *line, t_data *part)
{
	char *dup;

	dup = handle_env(line, part);
	escape_symbols(dup);
//	MAYBE THIS FREE ISN'T NEEDED
//	free_memory((void *)line);
	return (dup);
}

// NEED TO TEST
// line before quotations (and without quots, except escaped)
char	**handle_line(const char *line, t_data *part)
{
	char *dup;

	dup = handle_env(line, part);
	escape_symbols(dup);
//	redirections(dup);
//	MAYBE THIS FREE ISN'T NEEDED
//	free_memory((void *)line);
//	split???
	return (ft_split_pro(dup, ' '));
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

//	returns the part of str until redir symbol (include redir symbol)
t_data	*get_part(const char **line, char **env)
{
	size_t i;
	size_t f;
	size_t s;
	char r;
	char *quot;
	char *tmp;
	t_data *part;
	char **tmp_d;
	char **args;

//	MALLOC HERE
	part = ft_calloc(1, sizeof(t_data));
	i = 0;
	part->env = dup_env(env);
	args = (char **)malloc(sizeof(char **));
	*args = NULL;
	while (1)
	{
		s = catch_first_sign(*line + i, part, &r);
		if (r != '\'' && r != '"')
			break ;
		if ((tmp = ft_strchr(*line + i + s + 1, r)))
			f = tmp - (*line + i);
		else
		{
			ft_putendl_fd("Error quotation marks", 1);
//			need to determine what to return
			return (NULL);
		}
		args = ft_arrayjoin(args,
				handle_line(ft_substr(*line, i, s), part));
		quot = (r == '\'' ? ft_substr(*line, i + s + 1, f) :
				handle_quot(ft_substr(*line, i + s + 1, f), part));
		if (!(ft_strchr((const char *)(line + i + s - 1), ' ')))
		{
			f = ft_arraylen(args);
			tmp = args[f];
			args[f] = ft_strjoin(args[f], quot);
			free_memory(tmp);
		}
		else
		{
			tmp_d = (char **)malloc(sizeof(char **));
			tmp_d = &quot;
			args = (char **)ft_arrayjoin(args, tmp_d);
		}
		free_memory(quot);
		i += s + f + 2;
	}
	i += s + (part->type) ? 1 : 0;
	args = ft_arrayjoin(args, handle_line(ft_substr(*line, i, s), part));
	part->args = args;
	part->len = ft_arraylen(args);
	*line += i;
	return (part);
}

t_data		*parse(const char *line, char **env)
{
	t_data	*res;

	while (*line)
	{
		res = get_part(&line, env);
//		call here processing functions
	}
	return (res);
}
