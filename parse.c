/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:28:51 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/20 22:49:29 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(void **memory)
{
	free(*memory);
	*memory = NULL;
}

void	fill_type(t_data *part, char *symb, char **min, char *redir)
{
	if (!(ft_strncmp(symb, redir, 2)))
	{
		if (*redir == '<')
			part->type = 0;
		else
		{
			*min = symb + 1;
			part->type = REDIR_DR;
		}
	}
	else
	{
		*min = symb;
		if (*redir == '<')
			part->type = REDIR_L;
		else
			part->type = REDIR_R;
	}
}

// returns index of
int		is_linebreak(const char *str)
{
	char	*symb;
	size_t	min;

	min = ft_strlen(str);
	if ((symb = ft_strchr(str, SEMICOLON)) && min > symb - str && *(symb - 1) != '\\')
		min = symb - str;
	if ((symb = ft_strchr(str, PIPE)) && min > symb - str && *(symb - 1) != '\\')
		min = symb - str;
	return (min == ft_strlen(str) ? -1 : (int)min);
}

// returns index of
int		is_quotmark(const char *str)
{
	char	*symb;
	size_t	min;

	min = ft_strlen(str);
	if ((symb = ft_strchr(str, 39)) && min > symb - str && *(symb - 1) != '\\')
		min = symb - str;
	if ((symb = ft_strchr(str, '"')) && min > symb - str && *(symb - 1) != '\\')
		min = symb - str;
	return (min == ft_strlen(str) ? -1 : (int)min);
}

// returns index of closest redirection or quotation mark
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
	return (min != ft_strlen(str) ? min + 1 : ft_strlen(str));
}

// handle double quotation (substitute variables)
char	*handle_quotation(const char *line, size_t s, size_t f)
{
	char *quotation;

// move start
	if (s != 0)
		while ((s) && (ft_isalpha(line[s])))
			s--;
// move finish
	while ((line[++f]) && (ft_isalpha(line[f])) )
		;
//	+ substitution of variables
	return (quotation);
}

//	need to return variable's content (if not presented, empty line)
char 	*handle_env(const char *line, size_t *f/*, char **env*/)
{
	char 	*res;

	*f = 1;
	while ((line[*f]))
		if ((ft_isalnum(line[*f])) || line[*f] == '_')
			(*f)++;
//	res nov is the name of variable
//	MALLOC HERE
	res = ft_substr(line, 0, *f);
	return (res);
}

char 	*is_env(const char *line)
{
	char 	*tmp;

	if ((tmp = ft_strchr(line + n, '$')) && *(tmp - 1) != '\\')
	{
//		line before env
		dup = ft_substr(line, n, tmp - line);
		env = handle_env(tmp, &n);
//		MALLOC HERE
		dup1 = ft_strjoin(dup, env);
		free_memory((void **)&dup);
		free_memory((void **)&env);
	}
}

// line before quotations (and without quots, except shielded)
char	**handle_line(const char *line, size_t f)
{
	char 	*dup;
	char 	*dup1;
	char	*env;
	size_t	n;

//	MALLOC HERE
	n = 0;


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
		args = handle_line(*line + i, s - 1);
		quot = handle_quotation(*line, i + s, f);
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

