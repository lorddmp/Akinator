#ifndef TECHNIC
#define TECHNIC

#include "structs_and_types.h"

Node_t* Make_Node(TreeElem_t value, Node_t* n1 = NULL, Node_t* n2 = NULL);

void In_Node(TreeElem_t value, Node_t* node);

void Delete_Node(TreeElem_t bad_value, Node_t* node);

void Tree_Destructor(Node_t* node);

void Clean_Buffer(void);

void Skip_Spaces(int* position, char* massive);

#endif