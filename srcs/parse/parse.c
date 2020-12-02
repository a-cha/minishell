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

static int	concat_args(t_data *part, char *quot, char s)
{
	char 	**tmp_d;

	if (!(tmp_d = (char **)ft_calloc(2, sizeof(char *))))
	{
		free_memory(quot);
		return (-1);
	}
	tmp_d[0] = quot;
	tmp_d[1] = NULL;
	if (!(part->args = ft_arrjoin_pro(part->args, tmp_d, s)))
	{
		ft_arrayfree(tmp_d);
		return (-1);
	}
	return (0);
}

static int	quot_marks(const char *line, t_data *part, int s, char r)
{
	int		f;
	char	*quot;

	if ((f = is_closed_quot(line + s + 1, r)) < 0)
		f = ft_strlen(line + s + 1);
	if (!(quot = (r == '\'' ? ft_substr(line, s + 1, f) :
				  handle_quot(ft_substr(line, s + 1, f), part))))
		ft_exit(part, EXIT_FAILURE);
//		printf("\nquot\n");
//		printf("%s\n", quot);
	if ((concat_args(part, quot, *(line + s - 1))))
		ft_exit(part, EXIT_FAILURE);
//		*************
//		printf("\nft_arrjoin_pro\n");
//		print_d_array(part->args);
//		printf("\n");
//		*************
	return (f);
}

//	returns the part of str until redir symbol (include redir symbol)
static int	get_part(const char *line, t_data *part)
{
	int 	i;
	int 	s;
	char	r;

	i = 0;
	while (1)
	{
		s = catch_first_sign(line + i, part, &r);
		if (!(part->args = ft_arrjoin_pro(part->args, handle_line
		(ft_substr(line, i, s), part), *(line + i))))
			ft_exit(part, EXIT_FAILURE);
		if (!r)
			break ;
		i += s + 2 + quot_marks(line + i, part, s, r);
	}
	return (i + s + (!(part->type) ? 0 : 1));
}

int			parse(const char *line, t_data *part)
{
	int 	i;

	if ((weird_cases(line)))
	{
		last_status = 258;
		return (ft_strlen(line));
	}
	i = get_part(line, part);
	return (i);
}
