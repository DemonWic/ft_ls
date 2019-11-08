
#include "ft_ls.h"

time_t ft_difftime(time_t start,time_t end)
{
    return (start - end);
}

char    *ft_get_date(struct stat *buf)
{
    time_t now;
    time_t six_ago;
    time_t six_forward;
    char *res;
    char *buff;

    now = time(NULL);
    six_ago = ft_difftime(now,31556952 / 2);
    six_forward = ft_difftime(now, -31556952 / 2);
    res = (char *)malloc(sizeof(char) * 13);
    if (ft_difftime(six_ago, buf->st_mtime) > 0 || ft_difftime(buf->st_mtime, six_forward) > 0)  // вероятно нужна функция сравнения дат
    {
        buff = ft_strdup(ctime(&buf->st_mtime));
        ft_strncpy(res, &buff[4], 7);
        ft_strncpy(&res[7], &buff[19], 5);
        // year instead hour and minute
        free(buff);
    }
    else
    {
        buff = ft_strdup(ctime(&buf->st_mtime)); 
        // ft_printf("get - %s\n",buff);
        ft_strncpy(res, &buff[4], 12);  
        // ft_printf("get - %s\n",res);
        // res[12] = '\0'; 
        free(buff);
    }
    return (res);
}

static char    get_type_file(mode_t st_mode)
{
    char res;

    if (((st_mode) & S_IFMT) == S_IFSOCK)
        res = 's';
    else if (((st_mode) & S_IFMT) == S_IFLNK)
        res = 'l';
    else if (((st_mode) & S_IFMT) == S_IFREG)
        res = '-';
    else if (((st_mode) & S_IFMT) == S_IFBLK)
        res = 'b';
    else if (((st_mode) & S_IFMT) == S_IFDIR)
        res = 'd';
    else if (((st_mode) & S_IFMT) == S_IFCHR)
        res = 'c';
    else if (((st_mode) & S_IFMT) == S_IFIFO)
        res = 'p';
    else
        res = '?';
    return (res);
}

static char    ft_check_xattr(char *name)
{
    acl_t acl;
    ssize_t size;

    size = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
    if (size > 0)
        return ('@');
    else if ((acl = acl_get_link_np(name, ACL_TYPE_EXTENDED)) != NULL)
        {
            acl_free(acl);
            acl = NULL;
            return ('+');
        }
    else
        return (' ');

}

void    ft_get_permisson(mode_t st_mode, char *name)
{
    char res[12];

    // res =(char *)malloc(sizeof(char) * 12);
    res[0] = get_type_file(st_mode);
    res[1] = ((st_mode) & S_IRUSR) ? 'r' : '-';
    res[2] = ((st_mode) & S_IWUSR) ? 'w' : '-';
    res[3] = ((st_mode) & S_IXUSR) ? 'x' : '-';
    res[4] = ((st_mode) & S_IRGRP) ? 'r' : '-';
    res[5] = ((st_mode) & S_IWGRP) ? 'w' : '-';
    res[6] = ((st_mode) & S_IXGRP) ? 'x' : '-';
    res[7] = ((st_mode) & S_IROTH) ? 'r' : '-';
    res[8] = ((st_mode) & S_IWOTH) ? 'w' : '-';
    res[9] = ((st_mode) & S_IXOTH) ? 'x' : '-';
    if ((st_mode) & S_ISVTX)
        res[9] = ((st_mode) & S_IXOTH) ? 't' : 'T'; // липкий бит нужно посмотреть .
    res[10] = ft_check_xattr(name);
    res[11] = '\0';
    ft_printf("%s", res);
    ft_strclr(res);
}