#include "tree.h"
#include <stdio.h>

#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main()
{
    bool a = 1;
    // char* str = strdup("Это неизвестно кто");
    // Node_t* n1 = Make_Node(str);

    Node_t* n2 = Read_Tree();

    if (n2 == NULL)
    {
        printf("Read_Tree returned NULL\n");
        return 1;
    }

    while(a)
        a = Akinator(n2);
    
    Print_Tree(n2);

    FILE* fp = fopen(SAVE_TREE_FILE, "w");
    Save_Tree(n2, fp);
    fclose(fp);

    Tree_Destructor(n2);

    return 0;
}