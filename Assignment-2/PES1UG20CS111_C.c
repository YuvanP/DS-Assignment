#include "PES1UG20CS111_H.h"

int main()
{
    int vertices;
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

    printf("\nStart: (%d, %d)\nEnd: (%d, %d)\n", start.x, start.y, end.x, end.y);
    
    vertices = num_v(fp);
    v_node adj_list[vertices + 1];

    read_map(fp, adj_list);
    
    printf("\nDisplaying Adjacency List.\n");
    display_adj_list(adj_list, vertices);
}
