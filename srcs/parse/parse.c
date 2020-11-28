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
	if (*line == '?')
	{
		f = 1;
		env = ft_itoa(last_status);
	}
	else if (!(env = find_env(&(part->env), env)))
		env = ft_strdup("");
	free_memory(tmp);
	tmp = dup;
	if (!(dup = ft_strjoin(dup, env)))
		return (NULL);
	*s += f + 1;
	free_memory(tmp);
	free_memory(env);
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
		dup1 = ft_substr(line, i, (s == -1 ? ft_strlen(line + i) : s));
		tmp = dup;
		dup = ft_strjoin(dup, dup1);
		free_memory(tmp);
		free_memory(dup1);
		if (s == -1)
			break ;
		tmp = dup;
		dup = concatenate_env(dup, line + i + s + 1, &s, part);
		free_memory(tmp);
		i += s;
	}
	return (dup);
}

char		*handle_quot(char *line, t_data *part)
{
	char 	*dup;

	dup = handle_env(line, part);
	escape_symb_quot(dup);
	free_memory(line);
	return (dup);
}

char		**handle_line(char *line, t_data *part)
{
	char 	*dup;
	char 	**ret;

	dup = handle_env(line, part);
	escape_symb_line(dup);
//	redirections(dup);
	free_memory(line);
	ret = ft_split(dup, ' ');
	free_memory(dup);
	return (ret);
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

int 		concat_args(t_data *part, char *quot, char s)
{
	char 	**tmp_d;

	if (!(tmp_d = (char **)ft_calloc(2, sizeof(char *))))
		return (-1);
	tmp_d[0] = quot;
	tmp_d[1] = NULL;
	if (!(part->args = ft_arrjoin_pro(part->args, tmp_d, s)))
		return (-1);
	return (0);
}

//	returns the part of str until redir symbol (include redir symbol)
int 		get_part(const char *line, t_data *part)
{
	int 	i;
	int		f;
	int 	s;
	char	*quot;
	char 	**tmp_d;
//	i can do without this variable (but this is just one string)
	char	r;

	i = 0;
	while (1)
	{
		s = catch_first_sign(line + i, part, &r);
		tmp_d = part->args;
		if (!(part->args = ft_arrjoin_pro(part->args, handle_line
		(ft_substr(line, i, s), part), *(line + i))))
//			need to determine what to return
			return(ERR_MALLOC);
		ft_arrayfree(tmp_d);
//		*************
//		printf("\nft_arrjoin_pro\n");
//		print_d_array(part->args);
//		printf("\n");
//		*************
		if (!r)
			break ;
		if ((f = is_closed_quot(line + i + s + 1, r)) < 0)
//			need to determine what to return
			f = ft_strlen(line + i + s + 1);
		if (!(quot = (r == '\'' ? ft_substr(line, i + s + 1, f) :
				handle_quot(ft_substr(line, i + s + 1, f), part))))
			return(ERR_MALLOC);
//		printf("\nquot\n");
//		printf("%s\n", quot);
		if ((concat_args(part, quot, *(line + i + s - 1))))
			return(ERR_MALLOC);
//		*************
//		printf("\nft_arrjoin_pro\n");
//		print_d_array(part->args);
//		printf("\n");
//		*************
// 		ok with quoters with spaces
		i += s + f + 2;
	}
//		*************
//	printf("get_part\n");
//	print_d_array(part->args);
//	printf("\n");
//		*************
	return (i + s + (!(part->type) ? 0 : 1));
}

int			parse(const char *line, t_data *part)
{
	int 	i;

//	check weird cases (ls ;; ...)
	i = get_part(line, part);
	return (i);
}
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
