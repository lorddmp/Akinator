#ifndef TREE
#define TREE

#include <stdio.h>

typedef char* TreeElem_t;
#define SPEC "%s"

#define SAVE_TREE_FILE "Akinator_saved.txt"

struct Node_t
{
    TreeElem_t value;
    Node_t* left;
    Node_t* right;
};

Node_t* Read_Tree(void);

Node_t* Read_Node(int* position, char* massive);

Node_t* Make_Node(TreeElem_t value, Node_t* n1 = NULL, Node_t* n2 = NULL);

void In_Node(TreeElem_t value, Node_t* node);

void Delete_Node(TreeElem_t bad_value, Node_t* node);

bool Akinator(Node_t* node);

Node_t* Asking_Questions(Node_t* node);

int Get_Answer(void);

Node_t* Is_Object_Right(Node_t* node);

void Save_Tree(Node_t* node, FILE* fp);

void Print_Tree(Node_t* node);

void Print_Node(Node_t* node, FILE* fp);

void Tree_Destructor(Node_t* node);

void Clean_Buffer(void);

void Skip_Spaces(int* position, char* massive);

#endif