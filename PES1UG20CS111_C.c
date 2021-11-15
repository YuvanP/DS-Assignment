#include <stdio.h>
#include <stdlib.h>
#include "PES1UG20CS111_H.h"

int main()
{
    r_node *head = NULL;
    stack_e *stack_head = NULL;
    FILE *fp = fopen("test.txt", "r");

    if (fp == NULL)
    {
        printf("\nInput file does not exist");
        exit(EXIT_FAILURE);
    }

    coord start, end;
    getcord(&start, fp);
    getcord(&end, fp);

    printf("Start: (%d, %d)\nEnd: (%d, %d)\n", start.x, start.y, end.x, end.y);
    
    head = read_map(fp);
    fclose(fp);    

    display(head);

    // d_node *res;
    // res = search(head, 0, 2);
    // if (res != NULL)
    // {   
    //     if (res->right != NULL)
    //         printf("Right: (%d, %d) ", res->right->cord.x, res->right->cord.y);
    //     else
    //         printf("Right: %s ", (char *) res->right);
        
    //     if (res->down != NULL)
    //         printf("Down: (%d, %d)", res->down->cord.x, res->down->cord.y);
    //     else
    //         printf("Down: %s", (char *) res->down);
    // }
    // else
    //     printf("\nNode Doesn't exist");

    find_path(head, &start, &end, &stack_head);
    display_stack(stack_head);
}