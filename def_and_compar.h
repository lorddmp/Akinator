#ifndef DEF_AND_COMPAR
#define DEF_AND_COMPAR

#include "structs_and_types.h"

void Make_Path(Node_t* node, const char* value, bool* value_not_found, char* massive, int* position);

void Definition(Node_t* node, const char* value);

void Help_Definition(Node_t* node, const char* massive);

void Comparator(Node_t* node, const char* value1, const char* value2);

#endif