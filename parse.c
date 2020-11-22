/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:28:51 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/22 20:52:49 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(void **memory)
{
	free(*memory);
	*memory = NULL;
}

size_t	is_escaped(const char *line, size_t i)
{
	size_t	n;

	n = 0;
	if (i != 0)
	{
		while ((i--) && line[i] == '\\')
			n++;
	}
	return (n % 2);
}

// returns index of
int		is_linebreak(const char *str)
{
	char	*symb;
	size_t	min;

	min = ft_strlen(str);
	if ((symb = ft_strchr(str, SEMICOLON)) &&
							min > symb - str && !(is_escaped(str, symb - str)))
		min = symb - str;
	if ((symb = ft_strchr(str, PIPE)) &&
							min > symb - str && !(is_escaped(str, symb - str)))
		min = symb - str;
	return (min == ft_strlen(str) ? -1 : (int)min);
}

// returns index of
int		is_quotmark(const char *str)
{
	char	*symb;
	size_t	min;

	min = ft_strlen(str);
	if ((symb = ft_strchr(str, 39)) &&
							min > symb - str && !(is_escaped(str, symb - str)))
		min = symb - str;
	if ((symb = ft_strchr(str, '"')) &&
							min > symb - str && !(is_escaped(str, symb - str)))
		min = symb - str;
	return (min == ft_strlen(str) ? -1 : (int)min);
}

// returns index (or may be next index) of closest redirection or quotation mark
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
	return (min != ft_strlen(str) ? min/* + 1*/ : ft_strlen(str));
}

int		is_env(const char *line)
{
	char 	*tmp;

	return ((tmp = ft_strchr(line, '$')) && !(is_escaped(line, tmp - line)) ?
			(int)(tmp - line) : -1);
}

char 	*fill_env(char *env_name)
{
	char 	*env;

	env = "lol";
	free_memory((void **) &env_name);
	return (env);
}

char 	*handle_env(char *dup, const char *line, size_t *s)
{
	char	*env;
	char	*tmp;
	size_t	f;

	f = 1;
	while ((line[f]))
	{
		if ((ft_isalnum(line[f])) || line[f] == '_')
			f++;
	}
//	NEED TO FILL ENV HERE
	env = fill_env(ft_substr(line, 1, f - 1));
	tmp = dup;
	dup = ft_strjoin(dup, env);
	*s += f;
	free_memory((void **) &tmp);
	free_memory((void **) &env);
	return (dup);
}

void 	escaped_symbols(char *dup)
{
	size_t	i;
	size_t	r;

	i = -1;
	while (dup[++i])
	{
		if (dup[i] == '\\')
		{
			r = 0;
			while (dup[i + r++])
				dup[i + r] = dup[i + r + 1];
		}
	}
}

// line before quotations (and without quots, except escaped)
char	**handle_line(const char *line)
{
	char 	*dup;
	char 	*tmp;
	size_t	i;
	size_t	s;

	if ((s = is_env(line)))
	{
		i = 0;
		while ((s = is_env(line + i)))
		{
			if (!(dup = ft_substr(line, i, s)))
				return (NULL);
			tmp = dup;
			if (!(dup = handle_env(dup, line + s, &s)))
				return (NULL);
			free_memory((void **) &tmp);
			i += s;
		}
	}
	else
		if (!(dup = ft_strdup(line)))
			return (NULL);
//	escaped_symbols(dup);
	free_memory((void **)&line);
	return (ft_split(dup, ' '));
}

// handle double quotation (substitute variables)
char	*handle_quot_double(const char *line)
{
	char 	*dup;
	char 	*dup1;
	char	*env;
	size_t	i;
	size_t	s;

// move start
//	if (s != 0)
//		while ((s) && (ft_isalpha(line[s])))
//			s--;
// move finish
//	while ((line[++f]) && (ft_isalpha(line[f])) )
//		;
// CAN I MOVE IT TO ANOTHER FUNCTION?
	i = 0;
	dup = "\0";
	while ((s = is_env(line + i)))
	{
		dup1 = ft_substr(line, i, s);
		env = dup;
		dup = ft_strjoin(dup, dup1);
		free_memory((void **)&env);
		free_memory((void **)&dup1);
		env = handle_env(dup, line + i + s, &s);
		dup = ft_strjoin(dup, env);
		free_memory((void **)&env);
		i += s;
	}
//	+ substitution of variables
	free_memory((void **)&line);
	return (dup);
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
	split = malloc(sizeof(char *));
	*split = NULL;

	i = 0;
	s = 0;
	r = '\0';
//	i - index of next to first sign symbol (if not presented, index to the end of line)
//	r - quotation mark symbol
	while ((s = catch_first_sign(*line + i + s, part, &r)) && (r == '\'' || r == '"'))
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
		args = handle_line(ft_substr(*line, i, s - 1));
//		MALLOC HERE
		quot = (r == '\'' ? ft_substr(*line, i + s, f) : handle_quot_double(ft_substr(*line, i + s, f)));
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
