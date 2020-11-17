#include "minishell.h"

char *com[] = {
    "cd",
    "echo",
    "exit",
    "-n"
};

int ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void print_str(char **str)
{
    int i;

    i = 1;
    while (str[i + 1])
    {
        printf("%s", str[i]);
        i++;
        printf("%c", '\n');
    }
    printf("%s", str[i]);
    printf("%c", '\n');
}

int print_str_flag(char **str, int j)
{
    int i;

    i = 2;
    if (!str[i])
        return (0);
    while (str[i + 1])
    {
        printf("%s ", str[i]);
        i++;
    }
    printf("%s", str[i]);
    if (j == 1)
    {
        printf("%c", '%');
        printf("%c", '\n');
    }
    return (0);
}

int msh_echo(char *line, int j)
{
    char **str;

    str = ft_split(line, ' ');
    if (ft_strcmp(str[0], com[1]) == 0 && !str[1])
        write(1, "\n", 1);
    else if (ft_strcmp(str[0], com[1]) == 0 && ft_strcmp(str[1], com[3]) == 0)
        print_str_flag(str, j);
    else if (ft_strcmp(str[0], com[1]) == 0 && ft_strcmp(str[1], com[3]) != 0)
        print_str(str);
    return (1);
}

int main()
{
    char *line;
    char **str;
    int i;
    int j;

    line = ft_strdup("");
    printf("%s", "Login:");
    printf("%c", '\n');
    while (ft_strcmp(line, com[2]) != 0)
    {
        get_next_line(0, &line);
        str = ft_split(line, ';');
        j = 0;
        while (str[j])
            j++;
        i = 0;
        while (str[i])
        {
            msh_echo(str[i], j);
            j--;
            i++;
        }
    }
}