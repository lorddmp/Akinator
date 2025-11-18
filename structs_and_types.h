#ifndef STRUCTS_AND_TYPES
#define STRUCTS_AND_TYPES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>

#define IF_ERROR(arg)                                                                                   \
do {                                                                                                    \
    if (arg == NULL)                                                                                    \
    {                                                                                                   \
        fprintf(stderr, "ERROR in file: %s,\nfunction: %s,\n line: %d", __FILE__, __func__, __LINE__);  \
        return NULL;                                                                                    \
    }                                                                                                   \
} while (0)

typedef char* TreeElem_t;
#define SPEC "%s"

#define SAVE_TREE_FILE "Akinator_saved.txt"
#define DUMP_TREE_FILE "Tree_Dump.txt"

struct Node_t
{
    TreeElem_t value;
    Node_t* left;
    Node_t* right;
    Node_t* parent;
};

#endif