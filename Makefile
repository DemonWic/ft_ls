all:
	gcc -g -Wall -Wextra -Werror ft_ls.c time.c sort_time.c -L. -lft -lftprintf -o ft_ls
