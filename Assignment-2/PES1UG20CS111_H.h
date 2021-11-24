#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct coordinates
{
    int x;
    int y;
} coord;

typedef struct vertex_node
{
    int vid;
    coord loc;
    struct vertex_node *next;
} v_node;

// reading from file
void getcord(coord *, FILE *);
int num_v(FILE *);
void read_map(FILE *, v_node *);
void create_adj_list(v_node *, int);
void insert_vnode(v_node *, int, int);

// display functions
void display_adj_list(v_node *, int);
