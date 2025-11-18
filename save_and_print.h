#ifndef SAVE_AND_PRINT
#define SAVE_AND_PRINT

#include "structs_and_types.h"

void Save_Tree(Node_t* node, FILE* fp);

void Print_Tree(Node_t* node);

void Print_Node(Node_t* node, FILE* fp);

#endif