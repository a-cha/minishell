/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:38:39 by pcatrina          #+#    #+#             */
/*   Updated: 2020/11/22 15:44:55 by pcatrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_data  *data;
	char	*line;
	char	**env_dup;
	int		i;

	i = 0;
	data = malloc(sizeof (t_data));
	env_dup = (char **)malloc(8 * (ft_arraylen((void**)env) + 1));
	while (env[i])
	{
		env_dup[i] = ft_strdup(env[i]);
		i++;
	}
	data->env = env_dup;
	ft_putstr_fd(data->env[1], 1);
	while (1)
	{
		ft_putstr_fd("minishell > ", 1);
		get_next_line(1, &line);
		data->args = ft_split(line, ' ');
		data->len = ft_arraylen((void**)data->args);
		if (ft_strcmp(data->args[0], "cd") == 0)
            cd(data);
		else if (ft_strcmp(data->args[0], "pwd") == 0)
            pwd(data);
		else if (ft_strcmp(data->args[0], "echo") == 0)
		    echo(data);
        // parsed = parse(line);
	}
	return (0);
}
