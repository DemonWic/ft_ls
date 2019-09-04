#include <unistd.h>
#include <stdio.h>

void    ft_putstr(char *s)
{
    while(*s)
        write(1, s++, 1);
}

int     ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

int ft_check(char *s)
{
    int i;
    int j;
    char stek[1024];

    if (ft_strlen(s) == 0)
        return (0);
    i = 0;
    j = 0;
    stek[0] = 'A';
    while (s[i])
    {
        if (s[i] == '(')
            stek[++j] = '(';
        else if (s[i] == '[')
            stek[++j] = '[';
        else if (s[i] == '{')
            stek[++j] = '{';
        else if (s[i] == ')' && (stek[j] == '(' || j == 0))
            j--;
        else if (s[i] == ']' && (stek[j] == '[' || j == 0))
            j--;
        else if (s[i] == '}' && (stek[j] == '{' || j == 0))
            j--;
        i++;
    }
    // printf("i = %i j = %i", i , j);
    if (j == 0)
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
    int i;
    int res;

    if (argc < 2)
    {
        ft_putstr("\n");
        return (0);
    }

    i = 1;
    while(i < argc)
    {
        res = 0;
        res = ft_check(argv[i]);
        if (res == 1)
            ft_putstr("Error\n");
        else
            ft_putstr("OK\n");
        i++;
    }
    return (0);
}