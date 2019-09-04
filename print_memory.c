#include <stdio.h>
#include <unistd.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int     ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void    ft_putstr(char *s)
{
        write(1, s, ft_strlen(s));
}

// void    ft_printhex(int n)
// {
//     char c;
//     if (n >= 16)
//         ft_printhex(n / 16);
//     c = n % 16;
//     c = c < 10 ? c + 48 : c + 87;
//     ft_putchar(c);
// }

void    ft_printhex(int n)
{
    char c[3];
    int tmp;

    if (n < 16)
    {
        c[0] = '0';
        c[1] = (n % 16) < 10 ? ((n % 16) + 48) : ((n % 16) + 87);
        c[2] = '\0';
        ft_putstr(c);
    }
    else
    {
        tmp = n / 16;
        c[0] = (tmp % 16) < 10 ? ((tmp % 16) + 48) : ((tmp % 16) + 87);
        c[1] = (n % 16) < 10 ? ((n % 16) + 48) : ((n % 16) + 87);
        c[2] = '\0';
        ft_putstr(c);
    }
    
}

void	print_memory(const void *addr, size_t size)
{
    unsigned char *t = (unsigned char *)addr;
    size_t i;

    i = 0;
    int j;
    int tmp;
    tmp = 0;
    j = 0;

    while (i < size)
    {
        tmp = i;
        j = 0;
        while(j < 16 && i < size)
        {
            if (t[i] == 0)
            {
                ft_putchar('0');
                ft_putchar('0');
            }
            else
                ft_printhex(t[i]);
            if (j % 2)
                ft_putchar(' ');
            j++;
            i++;            
        }
        while(j < 16)
        {
            ft_putchar(' ');
            ft_putchar(' ');
            if (j % 2)
                ft_putchar(' ');
            j++;
        }
        j = 0;
        i = tmp;
        while (j < 16 && i < size)
        {
            if (t[i] > 31 && t[i] < 127)
                ft_putchar(t[i]);
            else
                ft_putchar('.');
            j++;
            i++;
        }
        ft_putchar('\n');
    }  
}


// #include <unistd.h>

// void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// void	ft_putstr(char *s)
// {
// 	while (*s)
// 		ft_putchar(*s++);
// }

// void	ft_printhex2(int n)
// {
// 	int c;

// 	if (n >= 16)
// 		ft_printhex2(n / 16);
// 	c = n % 16 + (n % 16 < 10 ? '0' : 'a' - 10);
//     // ft_putchar(' ');
// 	ft_putchar(c);
// }

// void	ft_printchars(unsigned char c)
// {
// 	ft_putchar((c > 31 && c < 127) ? c : '.');
// }

// void	print_memory(const void *addr, size_t size)
// {
// 	unsigned char *t = (unsigned char *)addr;
// 	size_t		i = 0;
// 	int			col;
// 	size_t		tmp = 0;

// 	while (i < size)
// 	{
// 		col = -1;
// 		tmp = i;
// 		while (++col < 16)
// 		{
// 			if (i < size)
// 			{
// 				if (t[i] < 16)
// 					ft_putchar('0');
// 				ft_printhex(t[i]);
// 			}
// 			else
// 				ft_putstr("  ");
// 			ft_putchar((i++ & 1) << 5);
// 			// ft_putchar((i++ & 1) << 5);
//             // printf(" A - %li ", ((i++ & 1) << 5));
            
// 		}
// 		col = -1;
// 		i = tmp;
// 		while (++col < 16 && i < size)
// 			ft_printchars(t[i++]);
// 		ft_putchar('\n');
// 	}
// }



int	main(void)
{
	int	tab[10] = {0, 23, 150, 255,
	              12, 16,  21, 42};
    // ft_printhex(23);
    // ft_putchar('\n');
	print_memory(tab, sizeof(tab));
	return (0);
}