#include "ft_ls.h"


static void merge(t_file *a, t_file *b, t_file **c)
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
    if ((ft_strcmp(a->name, b->name) < 0))  //a->value < b->value)
    {
        *c = a;
        a = a->next;
    } 
    else 
    {
        *c = b;
        b = b->next;
    }
    tmp.next = *c;
    while (a && b) 
    {
        if ((ft_strcmp(a->name, b->name) < 0))
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
        while (a)
        {
            (*c)->next = a;
            (*c) = (*c)->next;
            a = a->next;
        }
    if (b)
        while (b)
            {
                (*c)->next = b;
                (*c) = (*c)->next;
                b = b->next;
            }
    *c = tmp.next;
}

static void split(t_file *src, t_file **low, t_file **high)
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

void ft_merge_sort_a(t_file **head)
{
    t_file *low  = NULL;
    t_file *high = NULL;

    if ((*head == NULL) || ((*head)->next == NULL)) {
        return;
    }
    split(*head, &low, &high);
    ft_merge_sort_a(&low);
    ft_merge_sort_a(&high);
    merge(low, high, head);
}