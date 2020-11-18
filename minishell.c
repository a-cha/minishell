#include "minishell.h"

char *com[] = {
    "-n"
};

char    **fill_args(void)
{
    char **arg;
    char    *a = "/Users/acarnati/ fnvid fnvdf bivsdj";

    arg = ft_split(a, ' ');
    return (arg);
}

t_data inicial(t_data data)
{
    data.command = ECHO;
    data.args = fill_args();
    data.len = 4;
    data.type = 0;
    return(data);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int print_echo(t_data data)
{
	int i;

	i = 0;
	while(data.args[i + 1])
	{
		printf("%s", data.args[i]);
		printf("%c", ' ');
		i++;
	}
	printf("%s", data.args[i]);
	printf("%c", '\n');
	return (1);
}

int msh_echo(t_data data)
{
	int i;

	i = 1;
    if (ft_strcmp(data.args[0], com[0]) == 0)
	{
		while(data.args[i + 1])
		{
			printf("%s", data.args[i]);
			printf("%c", ' ');
			i++;
		}
		printf("%s", data.args[i]);
	}
    else if (ft_strcmp(data.args[0], com[0]) != 0)
        print_echo(data);
    return (1);
}

int msh_else()
{
    char *name[] = {"/bin/sh", NULL};
    execve (name[0], name, NULL);
    return(1);
}

int msh_cd(t_data data)
{
    DIR *pDir;

    if (data.len == 0) 
        return 1;
    pDir = opendir (data.args[0]);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", data.args[0]);
        return 1;
    }
    if (chdir(data.args[0]) != 0)
		strerror(chdir(data.args[0]));
    return 0;
}

int main(int ac, char **av, char **envp)
{
    t_data data;

    data.command = CD;
    data.args = fill_args();
    data.len = 1;
    data.type = 0;
    while (data.command != EXIT)
    {
        if (data.command == ECHO)
            msh_echo(data);
		if (data.command == CD)
            msh_cd(data);
		else if (data.command == LS)
			msh_else();
		data.command = LS;
    }
    return (0);
}
