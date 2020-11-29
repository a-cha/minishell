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
	char	*dup;
	char	*dup1;
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
		dup = concat_env(dup, line + i + s + 1, &s, part);
		free_memory(tmp);
		i += s;
	}
	return (dup);
}
