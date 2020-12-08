/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:54:04 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/27 15:54:05 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			process_status(void)
{
	int		child;
	int		status;

	if ((child = waitpid(-1, &status, 0)) == -1)
		return (-1);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = status | 128;
	if (last_pid == child)
		last_status = status;
	return (status);
}

int			is_first_symbol(const char *str, char c)
{
	if (!str)
		return (-1);
	else if (str[0] == c)
		return (0);
	return (-1);
}

char		*find_env(t_list **env_dup, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *env_dup;
	while (tmp)
	{
		env = tmp->content;
		if (!(ft_strcmp((const char *)env->env_name, str)))
			return (env->env_cont);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env		*find_env1(t_list **env_dup, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *env_dup;
	while (tmp)
	{
		env = tmp->content;
		if (!(ft_strcmp((const char *)env->env_name, str)))
			return (env);
		tmp = tmp->next;
	}
	return (NULL);
}
