#include <stdio.h>
#include <stdlib.h>

struct node
{
    int item;
    struct node * next;
};


int main()
{
    int num;
    struct node * head = NULL;
    struct node * prev;
    struct node * curr;   

    while (scanf("%d",&num) && num != 0)
    {
        curr = (struct node *)malloc(sizeof(struct node));

        if(head == NULL)
        {
            head = curr;
        }
        else
        {
            prev->next = curr;
        }
            curr->item = num;
            curr->next = NULL;
            prev = curr;
    }

    for(int i = 0; i < 5; i++)
    {
        printf("%d \n", head->item);
        head = head->next;
    }


    return 0;
}