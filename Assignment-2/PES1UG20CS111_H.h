#include <stdio.h>
#include <strings.h>

typedef struct coordinates
{
    int x;
    int y;
} coord;

// for graph
typedef struct vertex_node
{
    coord loc; // coordinates / location
    int vid; // vertex id
    struct vertex_node *right;
} v_node;

// for storing map
typedef struct col_node
{
    int col;
    struct col_node *right, *down;
} c_node;

typedef struct row_node
{
    int row;
    struct c_node *head;
    struct row_node *next;
} r_node;


// reading from file
void getcord(coord *, FILE *);
void read_map(FILE *, v_node **);
r_node *map(FILE *);
void insert_col(r_node *, c_node *, r_node *);

// display functions
void display_map(r_node *);