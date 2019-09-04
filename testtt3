#include <stdio.h>
#include <stdlib.h>



int  main()
{
    char *res;

    res = (char *)malloc(sizeof(char) * 4);
    *res = 's';
    *(++res) = 'a';
    *(++res) = 'p';
    *(++res) = '\0';
    res-=3;
    printf("%s\n", res);
    return (0);
}