#include "ft_ls.h"


// #  define ST_NBLOCKSIZE 1024
// #  define ST_NBLOCKS(statbuf) \
//   ((statbuf).st_size / ST_NBLOCKSIZE + ((statbuf).st_size % ST_NBLOCKSIZE != 0))
// # define ST_NBLOCKS2(statbuf) \
//   (S_ISREG ((statbuf).st_mode) || S_ISDIR ((statbuf).st_mode) ? \
//    st_blocks ((statbuf).st_size) : 0)

// # define NDIR   10

// # define BSIZE 1024

// #  define NINDIR (BSIZE / sizeof (daddr_t))

// #    define ST_NBLOCKS3(statbuf) \
//   (S_ISREG ((statbuf).st_mode) || S_ISDIR ((statbuf).st_mode) \
//    ? (statbuf).st_blocks * ((statbuf).st_blksize) / ST_NBLOCKSIZE : 0)


// off_t
// st_blocks (off_t size)
// {
//   off_t datablks = size / 512 + (size % 512 != 0);
//   off_t indrblks = 0;

//   if (datablks > NDIR)
//     {
//       indrblks = (datablks - NDIR - 1) / NINDIR + 1;

//       if (datablks > NDIR + NINDIR)
//         {
//           indrblks += (datablks - NDIR - NINDIR - 1) / (NINDIR * NINDIR) + 1;

//           if (datablks > NDIR + NINDIR + NINDIR * NINDIR)
//             indrblks++;
//         }
//     }

//   return datablks + indrblks;
// }
time_t ft_difftime(time_t start,time_t end)
{
    return (start - end);
}


char    get_type_file(mode_t st_mode)
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

// char    *get_perm_usr(mode_t st_mode)
// {
//     char *
//     if 
    
// }

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
        buff = ctime(&buf->st_mtime);
        ft_strncpy(res, &buff[4], 7);
        ft_strncpy(&res[7], &buff[19], 5);
        // year instead hour and minute
    }
    else
    {
        buff = ctime(&buf->st_mtime);  
        // ft_printf("get - %s\n",buff);
        ft_strncpy(res, &buff[4], 12);  
        // ft_printf("get - %s\n",res);
        // res[12] = '\0'; 
    }
    return (res);
}

char    ft_check_xattr(char *name)
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



char    *get_permisson(mode_t st_mode, char *name)
{
    char *res;

    res =(char *)malloc(sizeof(char) * 12);
    *res = get_type_file(st_mode);
    *(++res) = ((st_mode) & S_IRUSR) ? 'r' : '-';
    *(++res) = ((st_mode) & S_IWUSR) ? 'w' : '-';
    *(++res) = ((st_mode) & S_IXUSR) ? 'x' : '-';
    *(++res) = ((st_mode) & S_IRGRP) ? 'r' : '-';
    *(++res) = ((st_mode) & S_IWGRP) ? 'w' : '-';
    *(++res) = ((st_mode) & S_IXGRP) ? 'x' : '-';
    *(++res) = ((st_mode) & S_IROTH) ? 'r' : '-';
    *(++res) = ((st_mode) & S_IWOTH) ? 'w' : '-';
    *(++res) = ((st_mode) & S_IXOTH) ? 'x' : '-';
    if ((st_mode) & S_ISVTX)
        *res = ((st_mode) & S_IXOTH) ? 't' : 'T'; // липкий бит нужно посмотреть .
    *(++res) = ft_check_xattr(name);
    *(++res) = '\0';
    res -= 11;
    return (res);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    DIR *dir;
    struct dirent *entry;
    struct stat buff;
    struct passwd *usr;
    struct group *grp;

    
    dir = opendir(argv[1]);
    if (!dir) {
        perror("diropen");
        exit(1);
    };
    long int total;
    total = 0;
    char *res;
  
    while ( (entry = readdir(dir)) != NULL)
    {
        lstat(entry->d_name, &buff);
        res = get_permisson(buff.st_mode, entry->d_name);
        usr = getpwuid(buff.st_uid);
        grp = getgrgid(buff.st_gid); // -- usr->pw_name, grp->gr_name,
       
        ft_printf("%s %2li %s  %s  %5li %s %s\n", res, buff.st_nlink, usr->pw_name, grp->gr_name,buff.st_size,ft_get_date(&buff), entry->d_name);
        total += buff.st_blocks ;//* 512) / buff.st_blksize;
        // ft_printf("now - %li  cur - %li  raz - %li  raz2 - %li raz3 - %f\n", t, buff.st_mtime, (buff.st_mtime - t),(t - buff.st_mtime), difftime(t, buff.st_mtime));
        // ft_printf("%s\n",ft_get_date(&buff));
        // ft_printf("%li\n",buff.st_mtime);
        // if c
        //     k = 1; //file
        // if (((buff.st_mode) & 0170000) == 0040000)
        //     k = 50; //directory
        // int p = 0;
        // total += buff.st_blocks;
        // total2 += (buff.st_size / 512);
        // total3 += ST_NBLOCKS(buff);
        // if ((buff.st_mode) & 0000400)
        //     p = 20; //user read
        // if ((buff.st_mode) & 0000200)
        //     p += 15; //user write
        // if ((buff.st_mode) & 0000100)
        //     p += 10; //user execute
        // uid = buff.st_uid;
        // gid = buff.st_gid;
        // usr = getpwuid(uid);
        // grp = getgrgid(gid); // -- usr->pw_name, grp->gr_name,
        // // t_ptr = (time_t *)&buff.st_mtime;
        //  printf(" %2li  %4li" , buff.st_nlink ,buff.st_size);
        //  if (usr != NULL)
        //     printf(" %s",usr->pw_name);
        // else
        //     printf("    ");

        // if (grp != NULL)
        //     printf(" %s", grp->gr_name);
        // else
        //     printf("    ");
        //  printf("  %s\n", entry->d_name); //ctime(t_ptr)
        // printf("%ld - %s [%d] %d\n",
        //     entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
    }
    ft_printf("total : %li\n", total);


    closedir(dir);
    return (0);
}