#include "ft_ls.h"


31556952 / 2  // six month

char    *ft_get_date(time_t *date)
{
    time_t *now;
    time_t six_ago;
    time_t six_forward;
    char *res;

    now = time(NULL);
    six_ago = now - 31556952 / 2;
    six_forward = now + 31556952 / 2;
    res = (char *)malloc(sizeof(char) * 13);
    if (date < six_ago || date > six_forward)
    {
        // year instead hour and minute
    }
    else
    {
        res = ft_strncpy(res, ctime(date)[4], 12);
    }
    return (res);
}