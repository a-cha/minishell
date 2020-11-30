/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:00:45 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/23 20:43:57 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_filename(const char *line, char *flag)
{
	char 	*name;
	size_t	i;
	size_t	l;

	i = 0;
	name = NULL;
	while (line[i] && line[i] == ' ')
		i++;
	l = 0;
	while (line[i + l] && line[i + l] != ' ')
		l++;
	if (l == 0)
		*flag = 1;
	else
	{
		name = ft_substr(line, i, l);
		ft_memset((void *)(line + i), ' ', l);
	}
	return (name);
}

static int	set_redir(char *name, char flag, t_data *part)
{
	if (flag == '<')
	{
		if ((part->infile = open(name, O_RDONLY)) < 0)
			return (0);
		dup2(part->infile, 0);
	}
	else if (flag == '>')
	{
		if ((part->outfile = open(name,
									O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			return (0);
		dup2(part->outfile, 1);
	}
	else if (flag == 'd')
	{
		if ((part->outfile = open(name,
									O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
			return (0);
		dup2(part->outfile, 1);
	}
	return (1);
}

int			is_redir(const char *line, char *r)
{
	size_t	res;
	size_t	s;

	*r = 0;
	res = ft_strlen(line);
	if ((s = is_symb(line, '<')) < res)
	{
		res = s;
		*r = *(line + res);
	}
	if ((s = is_symb(line, '>')) < res)
	{
		res = s;
		*r = *(line + res);
		if (!(ft_strncmp(line + s, ">>", 2)))
			*r = 'd';
	}
	return (res == ft_strlen(line) ? -1 : (int)res);
}

void		redirections(char *line, t_data *part)
{
	int 	i;
	int 	s;
	char 	r;
	char	*name;
	char 	flag;

	i = 0;
	flag = 0;
	while ((s = is_redir(line + i, &r)) >= 0)
	{
		ft_memset(line + i + s, ' ', 1 + (r == 'd'));
		i += s + 1;
		if (!(name = get_filename(line + i, &flag)) && flag == 1)
//			further parse redir HOOOOOOOOW????
			;
		if (!(set_redir(name, r, part)))
		{
			free_memory(name);
			ft_exit(part, EXIT_FAILURE);
		}
		free_memory(name);
	}
}

/*
int 	main()
{
	char r;

	redirections(">>sfr> vfs><ver>>e",NULL);
}
*/
//	gcc srcs/parse/redirections.c srcs/parse/symbols.c libft/libft.a -I includes -I libft/includes

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
