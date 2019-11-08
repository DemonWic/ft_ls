
#include "ft_ls.h"


void    ft_print_file(t_file **root)
{
    t_file *buf;

    buf = *root;
    while (buf->next)
    {
        ft_printf("%s   ",buf->name);
        buf = buf->next;
    }
    ft_printf("%s\n", buf->name);
}


void    ft_print_file_full(t_file **root)
{
    t_file *buf;

    buf = *root;
    while (buf)
    {
        ft_get_permisson(buf->mode, buf->name);
        ft_printf(" %s\n", buf->name);
        buf = buf->next;
    }
    // ft_printf("%s\n", buf->name);
}



void    ft_add_info(struct dirent *entry, t_file *new)
{
    struct stat buff;

    lstat(entry->d_name, &buff);
    new->mode = buff.st_mode;
    new->uid = buff.st_uid;
    new->gid = buff.st_gid;
    new->nlink = buff.st_nlink; 
    new->size = buff.st_size;
    new->blocks = buff.st_blocks;
    new->time = buff.st_mtime;
}


t_file  *ft_new(const char *path, struct dirent *entry)
{
    t_file *new;
    char *buf;
    char *buf2;
 
    buf = ft_strjoin(path, "/");
    if (buf == NULL)
        return (NULL);
    buf2 = ft_strjoin(buf, entry->d_name);
    if (buf2 == NULL)
        return (NULL);
    free(buf);
    new =(t_file *)malloc(sizeof(t_file));
    if (new == NULL)
        return (NULL);
    new->name = ft_strdup((const char *)entry->d_name);
    if (new->name == NULL)
        return (NULL);
    new->path = ft_strdup((const char *)buf2);
    if (new->path == NULL)
        return (NULL);
    ft_add_info(entry, new);
    new->type = entry->d_type;
    new->next = NULL;
    free(buf2);
    return (new);
}

void    ft_create(const char *path, struct dirent *entry, t_file **root)
{
    t_file *new;
    t_file *buf;

    new = ft_new(path, entry);
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
        ft_create(path, entry, &root);
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

            ft_printf("%s:\n", buf->path);
            new_root = ft_read(buf->path);
            if (new_root)
            {
                ft_merge_sort_t(&new_root);
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
    // ft_merge_sort_t(&root);
    // ft_printf(".:\n");
    // ft_print_file(&root);
    ft_print_file_full(&root);
    // ft_print_all(&root, 1);
    ft_free(&root);
    return 0;
}