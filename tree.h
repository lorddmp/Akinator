#ifndef TREE
#define TREE

#include <stdio.h>

typedef const char* TreeElem_t;
#define SPEC "%s"

struct Node_t
{
    TreeElem_t value;
    Node_t* left;
    Node_t* right;
};

Node_t* Make_Node(TreeElem_t value, Node_t* n1 = NULL, Node_t* n2 = NULL);

void Print_Tree(Node_t* node);

void In_Node(TreeElem_t value, Node_t* node);

void Delete_Node(TreeElem_t bad_value, Node_t* node);

void Print_Node(Node_t* node, FILE* fp);

void Tree_Destructor(Node_t* node);

bool Akinator(Node_t* node);

void Clean_Buffer(void);

bool Get_Answer(char* choose);

#endif