#include "PES1UG20CS111_H.h"

void getcord(coord *c, FILE *fp)
{
    fscanf(fp, "%d %d\n", &c->x, &c->y);
}

/*
    First getting the number of 0's from the file which is then used to create the adjacency array (to get the size of array),
    Read from file again to start storing the 0's into the array, stores the vertex ID, coordinates.

    Then iterating through each element of the array to perform a check if any adjacent node exists, if it does, creates a node
    and inserts it into the array's next pointer.

    For each iteration, another iteration is performed up till x + 2, where x is the current iteration's x coordinate (to check for adjacency),
    after which if the condition matches for an adjacent node, the source (current iteration) and destination (second iteration) coordinates
    are sent to another function which will follow the insert at front method and insert it into the array's pointer.
*/

void read_map(FILE *fp, v_node *adj_list)
{
    int vertex = 1;
    int row = 1;
    int col = 1;
    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        switch (ch)
        {
        case '0':
            adj_list[vertex].next = NULL;
            adj_list[vertex].vid = vertex;
            adj_list[vertex].loc.x = row;
            adj_list[vertex].loc.y = col;

            vertex++;
            col++;
            break;

        case '1':
            col++;
            break;
        
        case '\n':
            col = 1;
            row++;
            break;
        
        default:
            break;
        }
    }

    create_adj_list(adj_list, vertex);
}

// returns the number of 0's from the file and sets file pointer to where it was initially
int num_v(FILE *fp)
{
    int vertices = 0;
    long int initial = ftell(fp);
    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '0')
            vertices++;
    }
    fseek(fp, initial, SEEK_SET);
    return vertices;
}

// creates and inserts a vertex node to the source's pointer variable
void insert_vnode(v_node *adj_list, int src, int dest)
{
    v_node *temp = (v_node *) malloc(sizeof(v_node));
    temp->loc = adj_list[dest].loc;
    temp->next = NULL;
    temp->vid = adj_list[dest].vid;

    // inserts at front
    if (adj_list[src].next != NULL)
    {
        temp->next = adj_list[src].next;
    }

    adj_list[src].next = temp;
}

// after creating the adjacency array, this creates the adjacency list by performing 2 iterations
void create_adj_list(v_node *adj_list, int vertices)
{
    coord curr, temp;
    for (int i = 1; i <= vertices; i++) // source
    {
        curr.x = adj_list[i].loc.x;
        curr.y = adj_list[i].loc.y;
        for (int j = i + 1; (j <= vertices) && (adj_list[j].loc.x < curr.x + 2); j++)
        {
            temp.x = adj_list[j].loc.x;
            temp.y = adj_list[j].loc.y;

            if ( (temp.x == curr.x && temp.y == curr.y + 1) // destination
                || (temp.y == curr.y && temp.x == curr.x + 1)
            )
            {
                insert_vnode(adj_list, i, j);
            }
        }
    }
}

void display_adj_list(v_node *adj_list, int vertices)
{
    v_node *temp; // for traversal
    printf("[VID, (x-cord, y-cord)]\n");
    for (int i = 1; i <= vertices; i++)
    {
        printf("\n[%2d, (%d, %d)]: ", adj_list[i].vid, adj_list[i].loc.x, adj_list[i].loc.y);
        
        temp = adj_list[i].next;
        while (temp != NULL)
        {
            if (temp->next != NULL)
                printf(" [%d, (%d, %d)] -->", temp->vid, temp->loc.x, temp->loc.y);
            else
                printf(" [%d, (%d, %d)]", temp->vid, temp->loc.x, temp->loc.y);
            temp = temp->next;
        }
    }
}
