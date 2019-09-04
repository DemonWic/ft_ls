#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>







int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    DIR *dir;
    struct dirent *entry;
    struct stat buff;
    struct passwd *usr;
    struct group *grp;
    // int k;
    // k = -1;
    // const time_t *t_ptr;
    // const char *s;

    // stat("ft_ls.c", &buff);
    // printf("%s\n", argv[0]);
    // printf("%li\n", buff.st_mtime);
    // t_ptr = (time_t *)&(buff.st_mtime);
    // s = ctime(t_ptr);
    // printf("%s\n", s);
    dir = opendir(argv[1]);
    if (!dir) {
        perror("diropen");
        exit(1);
    };
    // char user[4];
    // int h = 0;
    // while (h < 4)
    //     user[h++] = '-';
    // user[h] = '\0';
    // long int total;
    // long int total2;
    // long int total3;
    // // int k = 0;
    // total = 0;
    // total2 = 0;
    // total3 = 0;
    while ( (entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
        stat(entry->d_name, &buff);
        // if (((buff.st_mode) & 0170000) == 0100000)
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
        // usr = getpwuid(buff.st_uid);
        // grp = getgrgid(buff.st_gid);
        // t_ptr = (time_t *)&buff.st_mtime;
         printf(" %-*s\n", 5, getpwuid(buff.st_uid)->pw_name);
        // printf("%2li  %4li  %s\n", buff.st_nlink ,buff.st_size, entry->d_name); //ctime(t_ptr)
        // printf("%ld - %s [%d] %d\n",
        //     entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
    }
    // printf("total : %li\n", total);
    // printf("total2 : %li\n", total2);
    // printf("total3 : %li\n", total3);

//    2585  total  total_blocks gobble_file  ST_NBLOCKS

//  2939  mbswidth
/*
# if defined _POSIX_SOURCE || !defined BSIZE
#  define ST_NBLOCKS(statbuf) \
  ((statbuf).st_size / ST_NBLOCKSIZE + ((statbuf).st_size % ST_NBLOCKSIZE != 0))
# else
    This definition calls st_blocks, which is in the fileblocks module. */
/*
#  define ST_NBLOCKS(statbuf) \
  (S_ISREG ((statbuf).st_mode) || S_ISDIR ((statbuf).st_mode) ? \
   st_blocks ((statbuf).st_size) : 0)
# endif

# if defined hpux || defined __hpux__ || defined __hpux
   HP-UX counts st_blocks in 1024-byte units.
     This loses when mixing HP-UX and BSD file systems with NFS.  */
/*
#  define ST_NBLOCKSIZE 1024
# else  !hpux */
/*
#  if defined _AIX && defined _I386
     AIX PS/2 counts st_blocks in 4K units.  */
/*
#   define ST_NBLOCKSIZE (4 * 1024)
#  else
#   if defined _CRAY
#    define ST_NBLOCKS(statbuf) \
  (S_ISREG ((statbuf).st_mode) || S_ISDIR ((statbuf).st_mode) \
   ? (statbuf).st_blocks * ST_BLKSIZE (statbuf) / ST_NBLOCKSIZE : 0)
#   endif
#  endif
# endif*/
    closedir(dir);
    return (0);
}