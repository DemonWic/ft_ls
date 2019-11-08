# ifndef FT_LS_H
# define FT_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"



typedef struct		s_file
{
    char			*path;
    char            *name;
    mode_t          mode;
    nlink_t         nlink;
    uid_t           uid;
    gid_t           gid;
    time_t          time;
    off_t           size;
    blkcnt_t        blocks;
    unsigned char	 type;
    struct s_file	*next;
}					t_file;

void ft_merge_sort_a(t_file **head);
void ft_merge_sort_t(t_file **head);
time_t ft_difftime(time_t start,time_t end);
void    ft_get_permisson(mode_t st_mode, char *name);
// #define S_IFMT      0170000
// #define S_IFSOCK    0140000
// #define S_IFLNK	    0120000
// #define S_IFREG	    0100000
// #define S_IFBLK	    0060000
// #define S_IFDIR	    0040000
// #define S_IFCHR	    0020000
// #define S_IFIFO	    0010000

// #define S_IRUSR	    00400
// #define S_IWUSR	    00200
// #define S_IXUSR	    00100

// #define S_IRGRP     00040
// #define S_IWGRP	    00020	
// #define S_IXGRP	    00010

// #define S_IROTH	    00004
// #define S_IWOTH	    00002
// #define S_IXOTH	    00001

// #define S_ISVTX     01000




# endif