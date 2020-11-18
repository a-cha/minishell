/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:28:51 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/18 22:25:42 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//	returns index of redirection in str
int		is_redir(const char *str, t_data *part)
{
	char	*symb;
	char 	*min;

	min = (char *)(str - 1);
	if ((symb = ft_strchr(str, '|')))
	{
		min = symb;
		part->type = PIPE;
	}
	else if ((symb = ft_strchr(str, ';')) && min > symb)
	{
		min = symb;
		part->type = SEMIC;
	}
	if ((symb = ft_strchr(str, '<')) && min > symb)
		fill_type(part, symb, &min, "<<");
	if ((symb = ft_strchr(str, '>')) && min > symb)
		fill_type(part, symb, &min, ">>");
	return (min < str ? -1 : (int)(min - str));
}

// returns index of closest redirection or quotation mark
int		catch_tale(const char *str, t_data *part, char *r)
{
	char	*symb;
	char 	*min;
	int 	i;

	min = (char *)(str - 1);
	if ((i = is_redir(str, part)) != -1)
		min += i + 1;
	if ((symb = ft_strchr(str, 39)) && min > symb)
		min = symb;
	if ((symb = ft_strchr(str, '"')) && min > symb)
		min = symb;
	if (min < str)
	{
		part->type = 0;
		return (ft_strlen(str));
	}
	*r = *min;
	return ((int)(min - str) + 1);
}

// handle double quotation (substitute variables)
char	*handle_quotation(char *dup)
{
//	substitution of variables
	return (dup);
}

//	returns the part of str until redir symbol (include redir symbol)
t_data	*get_part(const char **line)
{
	size_t	i;
	size_t	f;
	size_t	e;
	char 	r;
	char	*quaters;
	char	*tmp;
	char	*str;
	t_data	*part;
	char	**split;
	char	**tmpd;

//	MALLOC HERE
	part = ft_calloc(1, sizeof(t_data));
	i = 0;
	split = malloc(sizeof(char *));
	*split = NULL;
//	i - index of next to tale symbol (if not presented index to '\0')
//	r - tale symbol
	while ((i += (e = catch_tale(*line + i, part, &r))) && (r == 39 || r == '"'))
	{
		if (!(tmp = ft_strchr(*line + i, r)))
		{
			ft_putendl_fd("Error quotation marks", 1);
//			need to determine what to return
			return (NULL);
		}
//		f - closes quotation mark
		else
			f = tmp - (*line + i);
//		str into quotation marks
//		MALLOC HERE
		quaters = ft_substr(*line, i, f);
		if (r == '"')
		{
//			need to replace variable to its content
//			tmp = quaters;
//			quaters = handle_quotation(quaters);
//			free(tmp);
//			tmp = NULL;
		}
//		MALLOC HERE
		str = ft_substr(*line, 0, i - 1);
//		MALLOC HERE
		tmpd = ft_split(str, ' ');
		free(str);
		str = NULL;
//		MALLOC HERE
		split = (char **)ft_arrayjoin((void **)split, (void **)tmpd);
		tmpd = malloc(sizeof(char *) * 2);
		*tmpd = quaters;
		tmpd[1] = NULL;
//		MALLOC HERE
		split = (char **)ft_arrayjoin((void **)split, (void **)tmpd);



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
		i += f + 1;
//		line now is the next to quotation marks symbol
//		i += i;
	}
	if ((part->type))
	{
		str = ft_substr(*line, i - e, e);
		i += e;
		tmpd = ft_split(str, ' ');
		free(str);
		str = NULL;
		split = (char **)ft_arrayjoin((void **)split, (void **)tmpd);
		/*
		dup = ft_strjoin(dup, str);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		*/
	}
	else
	{
		str = ft_substr(*line, i - e, e);
		i += e;
		tmpd = ft_split(str, ' ');
		free(str);
		str = NULL;
		split = (char **)ft_arrayjoin((void **)split, (void **)tmpd);
		/*
		str = ft_strdup(line);
		tmp = dup;
		dup = ft_strjoin(dup, str);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		free(str);
		str = NULL;
		*/
	}
	*line += i;
	part->args = split;
	part->len = ft_arraylen((void **)split);
	return (part);
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
		ft_printf("%s\n", *envp);
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
