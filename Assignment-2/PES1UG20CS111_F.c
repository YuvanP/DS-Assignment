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
    int row = 0;
    int col = 0;
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
            col = 0;
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
    printf("\nVID -> (x-cord, y-cord)\n");
    for (int i = 1; i <= vertices; i++)
    {
        printf("\n%2d -> (%d, %d): ", adj_list[i].vid, adj_list[i].loc.x, adj_list[i].loc.y);
        
        temp = adj_list[i].next;
        while (temp != NULL)
        {
            if (temp->next != NULL)
                printf(" [%d -> (%d, %d)] -->", temp->vid, temp->loc.x, temp->loc.y);
            else
                printf(" [%d -> (%d, %d)]", temp->vid, temp->loc.x, temp->loc.y);
            temp = temp->next;
        }
    }
}

int find_vertex(v_node *adj_list, coord *loc, int vertices)
{
    for (int i = 1; i <= vertices; i++)
    {
        if (adj_list[i].loc.x == loc->x && adj_list[i].loc.y == loc->y)
            return adj_list[i].vid;
    }
    return -1;
}

void find_path(v_node *adj_list, int startv, int endv, int vertices, int *dfsres, int *bfsres, int *dfspath, int *bfspath)
{
    if (endv == -1)
    {
        printf("\nDestination Vertex Not Found.");
    }
    else if (startv != -1)
    {
        int length = 0;
        int *visited = (int *) calloc(vertices + 1, sizeof(int));

        *dfsres = dfs(adj_list, startv, endv, vertices, visited, length, dfspath);
    }
    else
        printf("\nSource Vertex Not Found");
}

int dfs(v_node *adj_list, int s, int d, int vertices, int *visited, int length, int *path)
{
    int t;
    v_node *p;
    visited[s] = 1;

    for (p = (&adj_list[s])->next; p != NULL; p = p->next)
    {
        t = p->vid;
        if (visited[t] == 0)
        {
            length++;
            path[length] = t;
            if ((t == d) || dfs(adj_list, t, d, vertices, visited, length, path))
            {
                return 1;
            }
        }
    }
    length--;
    return 0;
}

void store_path(v_node *adj_list, int startv, int endv, int vertices, int dfsres, int bfsres, int *dfspath, int *bfspath)
{
    int temp;
    FILE *fpout_dfs = fopen("outdfs.txt", "w+");

    if (dfsres)
    {
        printf("\n---PATH FOUND by DFS---\n");
        fprintf(fpout_dfs, "%d -> (%d, %d)\n", adj_list[startv].vid, adj_list[startv].loc.x, adj_list[startv].loc.y);
        for (int i = 1; temp != endv; i++)
        {
            temp = dfspath[i];
            if (temp != 0)
            {
                fprintf(fpout_dfs, "%d -> (%d, %d)\n", adj_list[temp].vid, adj_list[temp].loc.x, adj_list[temp].loc.y);
            }
        }
    }
    else
    {
        printf("\n---PATH NOT FOUND by DFS---\n");
        fprintf(fpout_dfs, "%d\n", -1);
    }

    printf("\nOutput Files Generated.");
}
