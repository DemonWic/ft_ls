#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include "libft.h"

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        // if ((entry->d_name)[0] == '.')  -- shadow files and directories
        //         continue;
        if (entry->d_type == DT_DIR && !(ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0) ) 
        {
            char path[1024];
            // if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
            //     continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%s\n", path);
            listdir(path, indent + 2);
        } 
        else 
        {
            // printf("%*s- %s\n", indent, "", entry->d_name);
            printf("%i  %s\n", indent, entry->d_name);
        }
    }
    closedir(dir);
}

int main(void) {
    listdir(".", 0);
    return 0;
}