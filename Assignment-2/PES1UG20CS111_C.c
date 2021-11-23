#include <stdio.h>
#include <stdlib.h>
#include "PES1UG20CS111_H.h"

int main()
{
    v_node *adj_list;
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("\nInput file does not exist.");
        exit(EXIT_FAILURE);
    }

    printf("\nReading from input file.\n");
    coord start, end;
    getcord(&start, fp);
    getcord(&end, fp);

    // read_map(fp, &adj_list);
    r_node *first = map(fp);
    display_map(first);

    printf("\nStart: (%d, %d)\nEnd: (%d, %d)\n", start.x, start.y, end.x, end.y);
}
