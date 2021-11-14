#include <stdio.h>
#include <stdlib.h>
#include "PES1UG20CS111_H.h"

int main()
{
    r_node *head;
    stack_e *stack_head = NULL;
    head = NULL;
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

    find_path(head, &start, &end, &stack_head);
}