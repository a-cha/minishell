#include "libft.h"

typedef struct		s_data
{
	char 			**args;		// arguments (first - command, second - flags, further - arguments
	size_t			len;		// len of args array
	char 			type;		// type of redirection ('>', '<', '>>', '<<', '|', ';' or empty)
	struct s_data	*next;
	struct s_data	*prev;
}					t_data;

int		is_redir(const char *str)
{
	char	*symb;
	char 	*min;

	min = (char *)str;
	if ((symb = ft_strchr(str, '|')))
		min = symb;
	if ((symb = ft_strchr(str, ';')) && min > symb)
		min = symb;
	if ((symb = ft_strchr(str, '<')) && min > symb)
		min = symb;
	if ((symb = ft_strchr(str, '>')) && min > symb)
		min = symb;
	return (!symb ? -1 : (int)(min - str));
}

int		catch_tale(const char *str, char *r)
{
	char	*symb;
	char 	*min;
	int 	i;

	min = (char *)str;
	if ((i = is_redir(str)) != -1)
		min += i;
	if ((symb = ft_strchr(str, 39)) && min > symb)
		if (*(symb - 1) != '\\')
			min = symb;
	if ((symb = ft_strchr(str, '"')) && min > symb)
		if (*(symb - 1) != '\\')
			min = symb;
	if (!symb)
		return (-1);
	*r = *min;
	return ((int)(min - str));
}

size_t	catch_quote(const char *line, char c)
{
	char	*res;

	return (!(res = ft_strchr(line, c)) ? -1 : res - line);
}

void	handle_quote(char **dup)
{

}

char	*get_part(const char *line, size_t *i)
{
	size_t	f;
	char 	*dup;
	char 	r;
	char	*quaters;
	char	*tmp;

	*i = catch_tale(line, &r);
	if (r == 39 || r == '"')
	{
		if ((f = catch_quote(line + 1, r)) == -1)
		{
			ft_putendl_fd("Error quotation marks", 1);
			return (NULL);
		}
		quaters = ft_substr(line, *i + 1, f - (*i + 1));
		if (r == '"')
			handle_quote(&dup);
		tmp = ft_substr(line, 0, *i);
		dup = ft_strjoin(quaters, tmp);
		free(tmp);
		free(quaters);
		*i = f;
	}
	else if (r)
		dup = ft_substr(line, 0, *i + 1);
	else
		dup = ft_substr(line, 0, (*i = ft_strlen(line) - 1) + 1);
	return (dup);
}

char	**parse(const char *line)
{
	size_t	i;
	char	*res;
	char	**split;

	split = NULL;
	while (*line)
	{
		res = get_part(line, &i);
		line += i + 1;
		ft_printf("%s\n", res);
	}
	return (split);
}

int 	main()
{
	char	*line;
	char 	**parsed;
	int		r;

	r = 1;
	line = "kek";
	while (r > 0 && *line)
	{
		ft_putstr_fd("kekai > ", 1);
		r = get_next_line(1, &line);
		parsed = parse(line);
	}
//	while (*parsed)
//	{
//		ft_printf(">%s<\n", *parsed);
//		parsed++;
//	}
	return (0);
}
