/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_subst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:20:54 by sadolph           #+#    #+#             */
/*   Updated: 2020/11/29 22:20:56 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat_env(char *dup, const char *line, size_t *s, t_data *part)
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
		if (!(env = ft_itoa(last_status)))
		{
			free_memory(tmp);
			return (NULL);
		}
	}
	else if (!(env = find_env(&(part->env), env)))
	{
		if (!(env = ft_strdup("")))
		{
			free_memory(tmp);
			return (NULL);
		}
	}
	free_memory(tmp);
	tmp = dup;
	dup = ft_strjoin(dup, env);
	*s += f + 1;
	free_memory(tmp);
	free_memory(env);
	return (dup);
}

char		*handle_env(char *line, t_data *part)
{
	char	*dup;
	char	*dup1;
	char	*tmp;
	size_t	i;
	size_t	s;

	i = 0;
	if (!(dup = ft_strdup("")))
		ft_exit(part, EXIT_FAILURE);
	while (1)
	{
		s = is_symb(line + i, '$');
		if (!(dup1 = ft_substr(line, i, (s == -1 ? ft_strlen(line + i) : s))))
		{
			free_memory(dup);
			ft_exit(part, EXIT_FAILURE);
		}
		tmp = dup;
		if (!(dup = ft_strjoin(dup, dup1)))
		{
			free_memory(tmp);
			free_memory(dup1);
			ft_exit(part, EXIT_FAILURE);
		}
		free_memory(tmp);
		free_memory(dup1);
		if (s == -1)
			break ;
		if (!(dup = concat_env(dup, line + i + s + 1, &s, part)))
			ft_exit(part, EXIT_FAILURE);
		i += s;
	}
	return (dup);
}
