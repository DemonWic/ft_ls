#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "ft_ls.h"



typedef struct		s_file
{
    char			*path;
    char            *name;
    unsigned char	 type;
    struct s_file	*next;
}					t_file;

char	*ft_strdup(const char *s1)
{
	int		size;
	int		i;
	char	*res;

	i = 0;
	size = strlen(s1);
	res = (char *)malloc(size + 1);
	if (res == NULL)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


void merge(t_file *a, t_file *b, t_file **c)
{
    t_file tmp;
    *c = NULL;
    if (a == NULL)
    {
        *c = b;
        return;
    }
    if (b == NULL)
    {
        *c = a;
        return;
    }
    if ((strcmp(a->name, b->name) < 0))  //a->value < b->value)
    {
        *c = a;
        a = a->next;
    } else {
        *c = b;
        b = b->next;
    }
    tmp.next = *c;
    while (a && b) {
        if ((strcmp(a->name, b->name) < 0))
        {
            (*c)->next = a;
            a = a->next;
        }
        else
        {
            (*c)->next = b;
            b = b->next;
        }
        (*c) = (*c)->next;
    }
    if (a)
    {
        while (a)
        {
            (*c)->next = a;
            (*c) = (*c)->next;
            a = a->next;
        }
    }
    if (b)
    {
        while (b)
        {
            (*c)->next = b;
            (*c) = (*c)->next;
            b = b->next;
        }
    }
    *c = tmp.next;
}



void split(t_file *src, t_file **low, t_file **high)
{
    t_file *fast = NULL;
    t_file *slow = NULL;

    if (src == NULL || src->next == NULL)
    {
        (*low) = src;
        (*high) = NULL;
        return;
    }

    slow = src;
    fast = src->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    (*low) = src;
    (*high) = slow->next;
    slow->next = NULL;
}


void mergeSort(t_file **head)
{
    t_file *low  = NULL;
    t_file *high = NULL;
    if ((*head == NULL) || ((*head)->next == NULL)) {
        return;
    }
    split(*head, &low, &high);
    mergeSort(&low);
    mergeSort(&high);
    merge(low, high, head);
}


void    ft_print_file(t_file **root)
{
    t_file *buf;

    buf = *root;
    while (buf->next)
    {
        printf("%s   ",buf->name);
        buf = buf->next;
    }
    printf("%s\n", buf->name);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	char	*res;

	res = &s1[ft_strlen(s1)];
	i = 0;
	while (s2[i])
	{
		res[i] = s2[i];
		i++;
	}
	res[i] = '\0';
	return (s1);
}



char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*res;
	char	*con;

	i = 0;
	res = (char *)malloc(size + 1);
	if (res == NULL)
		return (NULL);
	con = res;
	while (i <= size + 1)
		res[i++] = '\0';
	return (con);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (NULL);
	r = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (r == NULL)
		return (NULL);
	while (s1[j] != '\0')
		r[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}


t_file  *ft_new(const char *path, char *name, unsigned char type)
{
    t_file *new;
    char *buf;
    char *buf2;
    // char tst[] = "/";

    // buf = (char *)malloc(sizeof(char) * (strlen(path) + strlen(name) + 2));
    // buf = ft_strnew((ft_strlen(path) + ft_strlen(name) + 1));
    // if (buf == NULL)
    //     return (NULL);
    buf = ft_strjoin(path, "/");
    if (buf == NULL)
        return (NULL);
    buf2 = ft_strjoin(buf, name);
    if (buf2 == NULL)
        return (NULL);
    free(buf);
    // ft_strcat(buf, path);
    // ft_strcat(buf, "/");
    // ft_strcat(buf, name);
    new =(t_file *)malloc(sizeof(t_file));
    if (new == NULL)
        return (NULL);
    new->name = ft_strdup((const char *)name);
    if (new->name == NULL)
        return (NULL);
    new->path = ft_strdup((const char *)buf2);
    if (new->path == NULL)
        return (NULL);
    new->type = type;
    new->next = NULL;
    free(buf2);
    return (new);
}

void    ft_create(const char *path, char *name, unsigned char type, t_file **root)
{
    t_file *new;
    t_file *buf;

    new = ft_new(path, name, type);
    buf = *root;
    if (new == NULL)
        return;
    if (*root != NULL)
    {
        while (buf->next)
            buf = buf->next;
        buf->next = new;
    }
    else
        *root = new;
}

t_file    *ft_read(const char *path)
{
    t_file *root;
    DIR *dir;
    struct dirent *entry;

    root = NULL;
    dir = opendir(path);
    if (dir == NULL)
        return (NULL);
    while ((entry = readdir(dir)) != NULL)
    {
        ft_create(path, entry->d_name, entry->d_type, &root);
    }
    closedir(dir);
    return (root);
}


void    ft_free(t_file **root)
{
    t_file *next;

    while(*root)
    {
        next = (*root)->next;
        free((*root)->name);
        free((*root)->path);
        free((*root));
        *root = next;
    }
    *root = NULL;
}

int    ft_print_all(t_file **root, int flag)
{

    t_file *buf;
    t_file *new_root;

    if (flag < -6)
        return (0);

    buf = *root;
    while (buf != NULL)
    {
        if ((buf->type == DT_DIR) && !(strcmp(buf->name, ".") == 0) && !(strcmp(buf->name, "..") == 0))
        {
        //    printf("here\n");

            printf("%s:\n", buf->path);
            new_root = ft_read(buf->path);
            if (new_root)
            {
                mergeSort(&new_root);
                ft_print_file(&new_root);
                ft_print_all(&new_root, (--flag));
                ft_free(&new_root);
             
            }

        }
        buf = buf->next;
    }
    return (1);

}


int main(void)
{
    t_file *root;

    root = ft_read(".");
    mergeSort(&root);
    printf(".:\n");
    ft_print_file(&root);
    ft_print_all(&root, 1);
    ft_free(&root);
    return 0;
}