#include <stdio.h>
#include <stdlib.h>
#include "PES1UG20CS111_H.h"

void getcord(coord *c, FILE *fp)
{
    fscanf(fp, "%d %d\n", &c->x, &c->y);
}

void insert_col(r_node *row, c_node *col, r_node *prow) // prow = prev row
{
    c_node *pres = row->head;

    if (prow == NULL) // still in the first row, so no previous row
    {
        if (pres == NULL)
        {
            row->head = col;
        }
        else
        {
            while (pres->right != NULL)
            {
                pres = pres->right;
            }
            pres->right = col;
        }
    }
    else // second row onwards
    {
        c_node *prev;
        prev = prow->head;
        if (pres == NULL)
        {
            row->head = col;
            prev->down = col;
            // linking previous' down to current row's node
        }
        else
        {
            while (pres->right != NULL)
            {
                pres = pres->right;
                prev = prev->right;
                // traversing direct above node along with present node
            }
            
            pres->right = col;
            prev->right->down = col;
        }
    }
}

r_node *map(FILE *fp)
{
    char ch;
    int flag = 1;
    int row = 1;
    int col = 1;
    r_node *temp_row, *first, *prev_row = NULL;
    c_node *temp_col;

    while((ch = fgetc(fp)) != EOF)
    {
        if (flag)
        {
            temp_row = (r_node *) malloc(sizeof(r_node));
            temp_row->next = NULL;
            temp_row->head = NULL;
            temp_row->row = row;

            if (prev_row == NULL)
                first = temp_row;
            else
                prev_row->next = temp_row;
            
            flag = 0;
        }

        switch (ch)
        {
        case '0':
        case '1':
            temp_col = (c_node *) malloc(sizeof(c_node));
            temp_col->right = temp_col->down = NULL;
            temp_col->col = col;

            insert_col(temp_row, temp_col, prev_row);
            col++;
            break;
        
        case '\n':
            prev_row = temp_row;
            row++;
            flag = 1;
            col = 1;
            break;
        
        default:
            break;
        }
    }
}

void display_map(r_node *first)
{
    printf("\n");
    c_node *col;
    while (first != NULL)
    {
        col = first->head;

        while (col != NULL)
        {
            printf("(%d, %d) ----> (%d, %d) ", first->row, col->col, first->next->row, col->down->col);;
            col = col->right;
        }
        first = first->next;
    }
}

void read_map(FILE *fp, v_node **adj_list)
{
    
}
