#include "libft.h"

typedef struct		s_data
{
	char 			**args;		// arguments (first - command, second - flags, further - arguments
	size_t			len;		// len of args array
	char 			type;		// type of redirection ('>', '<', '>>', '<<', '|', ';' or empty)
	struct s_data	*next;
	struct s_data	*prev;
}					t_data;

//	returns index of redirection in str
int		is_redir(const char *str)
{
	char	*symb;
	char 	*min;

	min = (char *)(str - 1);
	if ((symb = ft_strchr(str, '|')))
		min = symb;
	if ((symb = ft_strchr(str, ';')) && min > symb)
		min = symb;
	if ((symb = ft_strchr(str, '<')) && min > symb)
		min = symb;
	if ((symb = ft_strchr(str, '>')) && min > symb)
		min = symb;
	return (min < str ? -1 : (int)(min - str));
}

int		catch_tale(const char *str, char *r)
{
	char	*symb;
	char 	*min;
	int 	i;

	min = (char *)(str - 1);
	if ((i = is_redir(str)) != -1)
		min += i;
	if ((symb = ft_strchr(str, 39)) && min > symb)
		min = symb;
	if ((symb = ft_strchr(str, '"')) && min > symb)
		min = symb;
	if (min < str)
	{
		*r = 0;
		return (ft_strlen(str));
	}
	*r = *min;
	return ((int)(min - str) + 1);
}

size_t	catch_quote(const char *line, char c)
{
	char	*res;

	res = ft_strchr(line, c);
	return (!res ? -1 : res - line);
}

char	*handle_quote(char *dup)
{
//	substitution of variables
	return (dup);
}

//	returns the part of str until redir symbol (include redir symbol)
char	*get_part(const char *line, size_t *i)
{
	size_t	f;
	size_t	e;
	char 	*dup;
	char 	r;
	char	*quaters;
	char	*tmp;
	char	*str;

//	i - index of next to tale symbol
//	r - tale symbol
	dup = NULL;
	while ((*i += (e = catch_tale(line + *i, &r))) && (r == 39 || r == '"'))
	{
//		f - closes quotation mark
		if ((f = catch_quote(line + *i, r)) == -1)
		{
			ft_putendl_fd("Error quotation marks", 1);
			return (NULL);
		}
//		str into quotation marks
		quaters = ft_substr(line, *i, f);
		if (r == '"')
		{
//			tmp = quaters;
//			quaters = handle_quote(quaters);
//			free(tmp);
//			tmp = NULL;
		}
		str = ft_substr(line, 0, *i - 1);
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
		*i += f + 1;
//		line now is the next to quotation marks symbol
//		*i += *i;
	}
	if (r)
	{
		str = ft_substr(line, *i - 1, e);
		tmp = dup;
		dup = ft_strjoin(dup, str);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		free(str);
		str = NULL;
	}
	else
	{
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
	}
	return (dup);
}

t_data	*create_part(char *res)
{
	t_data	*part;
	size_t	len;

	if (!(part = malloc(sizeof(t_data))))
	{
//		free some? and what is the error must return
		return (NULL);
	}
	len = ft_strlen(res);
	if ((is_redir(res + len -1)))
	{
		part->type = res[len - 1];
		res[len - 1] = '\0';
	}
	else
		part->type = 0;
	part->args = ft_split(res, ' ');
}

char	**parse(const char *line)
{
	size_t	i;
	char	*res;
	t_list	*list;
	t_list	**head;

	char	**split = NULL;

	head = &list;
	i = 0;
	while (*line)
	{
//		returns the part of str until redir symbol (include redir symbol)
		res = get_part(line, &i);
/*		if (!(list = ft_lstnew(create_part(res))))
		{
//		free some? and what is the error must return
			return (NULL);
		}*/
		ft_printf(">%s<\n", res);
//		line now is next to redirect symbol
		line += i;
	}
	return (split);
}

int 	main()
{
	char	*line;
	char 	**parsed;
	int		r;

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
