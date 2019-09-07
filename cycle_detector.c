
typedef struct s_list
{
    int data;
    struct s_list *next;
}   t_list;

int cycle_detector(const t_list *list)
{
    const t_list *fast;
    const t_list *slow;
    if (!list)
        return (0);
    fast = list;
    slow = list;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = (fast->next)->next;
        if (fast == slow)
            return (1);
    }
    return (0);
}

#include <stdio.h>
#include <stdlib.h>


int main()
{
    t_list *l1;
    t_list *l2;
    t_list *l3;
    t_list *l4;

    l1 = (t_list *)malloc(sizeof(t_list));
    l2 = (t_list *)malloc(sizeof(t_list));
    l3 = (t_list *)malloc(sizeof(t_list));
    l4 = (t_list *)malloc(sizeof(t_list));

    l1->next = l2;
    l2->next = l3;
    l3->next = l4;
    l4->next = l2;
    int p;

    p = cycle_detector(l1);
    printf("%i\n", p);
}
