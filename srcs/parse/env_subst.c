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

static char	*fill_env(char *env, char q, size_t *f, t_data *part)
{
	char	*ret;

	if (q == '?')
	{
		*f = 1;
		ret = ft_itoa(last_status);
	}
	else if (!(ret = find_env(&(part->env), env)))
		ret = ft_strdup("");
	else
		ret = ft_strdup(ret);
	free_memory(env);
	return (ret);
}

static char	*concat_env(char *dup, const char *line, size_t *s, t_data *part)
{
	char	*env;
	char	*tmp;
	size_t	f;

	f = 0;
	while ((line[f]) && ((ft_isalnum(line[f])) || line[f] == '_'))
		f++;
	if (!(env = ft_substr(line, 0, f)))
		ft_exit(part, EXIT_FAILURE);
	if (!(env = fill_env(env, *line, &f, part)))
		ft_exit(part, EXIT_FAILURE);
	tmp = dup;
	dup = ft_strjoin(dup, env);
	*s += f + 1;
	free_memory(tmp);
	free_memory(env);
	return (dup);
}

void		free_and_exit(char *s1, char *s2, t_data *part, char flag)
{
	if (s1)
		free_memory(s1);
	if (s2)
		free_memory(s2);
	if (flag == 1)
		ft_exit(part, EXIT_FAILURE);
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
			free_and_exit(dup, NULL, part, 1);
		tmp = dup;
		if (!(dup = ft_strjoin(dup, dup1)))
			free_and_exit(dup1, tmp, part, 1);
		free_and_exit(dup1, tmp, part, 0);
		if (s == -1)
			break ;
		dup = concat_env(dup, line + i + s + 1, &s, part);
		i += s;
	}
	return (dup);
}
