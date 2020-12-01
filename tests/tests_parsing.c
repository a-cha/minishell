//
// Created by Skipjack Adolph on 11/22/20.
//

#include "minishell.h"
#include "get_next_line.h"

int		is_linebreak(const char *str);
int		is_quotmark(const char *str);
size_t	catch_first_sign(const char *str, t_data *part, char *r);

int			main(int ac, char **av, char **env)
{
	char 	r;
//	char 	*dup = "echo HOME";
	char 	*dup = "echo he'll'o \"$HOME' l'ol\" kek; $LOGNAME resw"; // 7/10 13/25 31 44
	t_data	*res;
	char	**args;
	size_t	i;

//
/*
	t_data	*part;
	int 	n;
	char 	*line;

	part = ft_calloc(1, sizeof(t_data));
	part->env = dup_env(env);
	n = 0;
	while (1)
	{
		ft_putstr_fd("Вводи > ", 1);
		get_next_line(0, &line);
		reset_t_data(part);
		while (*line)
		{
			if ((n = parse(line, part)) < 0)
				return (-1);
//			call processing here, remove line below
			print_d_array(part->args);
			line += n;
		}
	}
	//		call here processing functions
*/
//	test ft_arrjoin_pro
	args = ft_arrjoin_pro(ft_split("a b c", ' '),
					   ft_split("d e f", ' '), ' ');
	i = -1;
	while (args[++i] != NULL)
		printf(">%s<\n", args[i]);
/*
//	test handle_quot
	part->env = dup_env(env);
	printf(">%s<\n>%s<\n", dup, handle_quot(dup, part));
*/
/*
//	test escape_symbols
	while (1)
	{
		ft_putstr_fd("kekai > ", 1);
		get_next_line(1, &line);
		escape_symbols(line);
		printf("%s\n", line);
	}
*/
/*
//	test is_symb
	while (1)
	{
		ft_putstr_fd("kekai > ", 1);
		get_next_line(1, &line);
		if ((n = is_symb(line)) > -1)
		{
			printf("ret: %d\n", n);
			printf("%s\n", line + n);
		}
		else
			printf("-1\n");
	}
*/
/*
//	test is_linebreak
	while (1)
	{
		ft_putstr_fd("kekai > ", 1);
		get_next_line(1, &line);
//		printf("%zu\n", is_escaped(line, 5));
		if ((n = is_linebreak(line)) != -1)
			printf("%s\n", line + n);
		else
			printf("-1\n");
	}
*/
/*
//	test is_quotmark
	while (1)
	{
		ft_putstr_fd("kekai > ", 1);
		get_next_line(1, &line);
		if ((n = is_quotmark(line)) != -1)
			printf("%s\n", line + n);
		else
			printf("-1\n");
	}
*/
/*
//	test catch_first_sign
	while (1)
	{
		ft_putstr_fd("kekai > ", 1);
		get_next_line(1, &line);
		if ((n = catch_first_sign(line, part, &r)) != -1)
		{
			printf("ret: %d\n", n);
			printf("%s\n%c\n%c\n", line + n, part->type, r);
		}
}*/
	return (0);

}
