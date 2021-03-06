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

static char	*get_filename(const char *line)
{
	char	*name;
	size_t	i;
	size_t	l;

	i = 0;
	name = NULL;
	while (line[i] && !is_symb(&line[i], ' '))
		i++;
	l = 0;
	while (line[i + l] && is_symb(&line[i + l], ' ') &&
	is_symb(&line[i + l], ';') && is_symb(&line[i + l], '|') &&
	is_symb(&line[i + l], '>') && is_symb(&line[i + l], '<'))
		l++;
	name = ft_substr(line, i, l);
	ft_memset((void *)(line + i), ' ', l);
	return (name);
}

static int	set_redir(char *name, char flag, t_data *part)
{
	if (flag == '<')
	{
		if (part->infile >= 0)
			close(part->infile);
		if ((part->infile = open(name, O_RDONLY)) < 0)
		{
			print_error(0, strerror(errno), 1);
			g_last_status = 1;
			return (-1);
		}
	}
	else
	{
		if (part->outfile >= 0)
			close(part->outfile);
		if ((part->outfile = open(name,
		O_WRONLY | O_CREAT | (flag == '>' ? O_TRUNC : O_APPEND), 0644)) < 0)
			return (1);
	}
	return (0);
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
	int		i;
	int		s;
	char	r;
	char	*name;

	i = 0;
	while ((s = is_redir(line + i, &r)) >= 0)
	{
		ft_memset(line + i + s, ' ', 1 + (r == 'd'));
		i += s + 1;
		if (!(name = get_filename(line + i)))
			ft_exit(part, EXIT_FAILURE);
		if ((r = (char)set_redir(name, r, part)))
		{
			free_memory(name);
			if (r == 1)
				ft_exit(part, EXIT_FAILURE);
			part->infile = -2;
			break ;
		}
		free_memory(name);
	}
}
