/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:28:51 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 22:05:12 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	escape_symbols(char *dup)
{
	size_t	i;
	size_t	r;

	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '\\')
		{
			r = -1;
			while (dup[i + ++r])
				dup[i + r] = dup[i + r + 1];
		}
	}
}

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
	if ((s = is_symb(line, SEMICOLON)) < res)
		res = s;
	if ((s = is_symb(line, PIPE)) < res)
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

char 	*handle_env(char *dup, const char *line, size_t *s, t_data *part)
{
	char	*env;
	char	*tmp;
	size_t	f;

	f = 0;
	while ((line[f]) && (ft_isalnum(line[f])) || line[f] == '_')
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

// handle double quotation (substitute variables)
char	*handle_quot(const char *line, t_data *part)
{
	char 	*dup;
	char 	*dup1;
	char	*tmp;
	size_t	i;
	size_t	s;

	i = 0;
	dup = ft_strdup("");
	while ((s = is_symb(line + i, '$')) != -1)
	{
		dup1 = ft_substr(line, i, s);
		tmp = dup;
		dup = ft_strjoin(dup, dup1);
		free_memory((void *)tmp);
		free_memory((void *)dup1);
		dup = handle_env(dup, line + i + s + 1, &s, part);
		i += s;
	}
	dup1 = ft_substr(line, i, ft_strlen(line + i));
	tmp = dup;
	dup = ft_strjoin(dup, dup1);
	free_memory((void *)tmp);
	free_memory((void *)dup1);
//	+ redirections
//	MAYBE THIS FREE ISN'T NEED
//	free_memory((void *)line);
	return (dup);
}

// NEED TO TEST
// line before quotations (and without quots, except escaped)
char	**handle_line(const char *line, t_data *part)
{
	char 	*dup;
	char 	*tmp;
	size_t	i;
	size_t	s;

	if ((s = is_symb(line, '$')))
	{
		i = 0;
		while ((s = is_symb(line + i, '$')))
		{
			tmp = dup;
			if (!(dup = ft_substr(line, i, s)))
				return (NULL);
			free_memory((void *)tmp);
			tmp = dup;
			if (!(dup = handle_env(dup, line + s + 1, &s, part)))
				return (NULL);
			free_memory((void *)tmp);
			i += s;
		}
	}
	else
		if (!(dup = ft_strdup(line)))
			return (NULL);
//	escaped_symbols(dup);
//	redirections(dup);
	free_memory((void *)line);
	return (ft_split(dup, ' '));
}

//	returns the part of str until redir symbol (include redir symbol)
t_data	*get_part(const char **line)
{
	size_t i;
	size_t f;
	size_t s;
	char r;
	char *quot;
	char *tmp;
	char *str;
	t_data *part;
	char **split;
	char **tmpd;
	char **args;

//	MALLOC HERE
	part = ft_calloc(1, sizeof(t_data));
//	split = malloc(sizeof(char *));
//	*split = NULL;

	i = 0;
	s = 0;
//	i - index of next to first sign symbol (if not presented, index to the end of line)
//	r - quotation mark symbol
	while ((s = catch_first_sign(*line + i + s, part, &r)) &&
													(r == '\'' || r == '"'))
	{
		if (!(tmp = ft_strchr(*line + i + s, r)))
		{
			ft_putendl_fd("Error quotation marks", 1);
//			need to determine what to return
			return (NULL);
		}
//		f - index of closes quotation mark
		else
			f = tmp - (*line + i);
//		MALLOC HERE
//		quaters = ft_substr(*line, i, f);
		args = handle_line(ft_substr(*line, i, s - 1), part);
//		MALLOC HERE
		quot = (r == '\'' ? ft_substr(*line, i + s, f) :
				handle_quot(ft_substr(*line, i + s, f), part));
//		free(tmp);
//		tmp = NULL;
/*
		tmp = dup;
		dup = ft_strjoin(dup, str);
		free(str);
		str = NULL;
		free(tmp);
		tmp = NULL;
		tmp = dup;
		dup = ft_strjoin(dup, quaters);
		free(tmp);
		tmp = NULL;
		free(quaters);
		quaters = NULL;
*/
		i += s;
		s = 0;

/*

		i += f + 1;
//		line now is the next to quotation marks symbol
//		i += i;
	}
	str = ft_substr(*line, i - e, e);
	i += e;
	tmpd = ft_split(str, ' ');
	free(str);
	str = NULL;
	split = (char **) ft_arrayjoin((void **) split, (void **) tmpd);*/
/*
		dup = ft_strjoin(dup, str);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		*//*

	*line += i;
	part->args = split;
	part->len = ft_arraylen((void **)split);
	return (part);
*/
	}
	return (NULL);
}

t_list	**parse(const char *line)
{
	t_data	*res;
	t_list	**head;

	head = malloc(sizeof(t_list *));
	*head = NULL;
	while (*line)
	{
		res = get_part(&line);
		ft_lstadd_back(head, ft_lstnew(res));
/*		if (!(list = ft_lstnew(create_part(res))))
		{
//		free some? and what is the error must return
			return (NULL);
		}*/
//		line now is next to redirect symbol
	}
	return (head);
}

/*
int 	main(int ac, char **av, char **envp)
{
	char	*line;
	t_list 	**parsed;
	int		r;

	while (envp)
	{
//		forbidden function
		printf("%s\n", *envp);
		envp++;
	}
	r = 1;
	line = " ab \"c ' de\"; '| \"'   n | opqr'st';uvwxyz";
	while (r > 0 && *line)
	{
//		ft_putstr_fd("kekai > ", 1);
//		r = get_next_line(1, &line);
		parsed = parse(line);
	}
//	while (*parsed)
//	{
//		ft_printf(">%s<\n", *parsed);
//		parsed++;
//	}
	return (0);
}
*/
