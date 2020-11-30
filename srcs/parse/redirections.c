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

void 		redir_right()
{

}

void 		redir_left()
{

}

void 		redir_d_right()
{

}

char 		*get_filename(const char *line)
{
	char 	*name;
	size_t	i;
	size_t	l;

	i = -1;
	while (line[++i] == ' ')
		;
	l = -1;
	while (line[i + ++l] != ' ')
		;
	name = ft_substr(line, i, l);
	return (name);
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

int			redirections(char *line, t_data *part)
{
	int 	i;
	int 	s;
	char 	r;

	i = 0;
	while ((s = is_redir(line + i, &r)) >= 0)
	{
		printf("%d\t%c\n", i + s, r);
		i += s + 1 + (r == 'd');
	}
	return (0);
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

/*
int 	main()
{
	char r;

//	printf("%s\n", get_filename("   fnlkerjnvs472674?fs    "));
	redirections(">>sfr> vfs><ver>>e",NULL);
}
//gcc srcs/parse/redirections.c srcs/parse/symbols.c libft/libft.a -I includes -I libft/includes
*/
