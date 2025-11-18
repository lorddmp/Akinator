#include "Akinator.h"
#include "def_and_compar.h"
#include "reading_tree.h"
#include "save_and_print.h"
#include "structs_and_types.h"
#include "technic_func.h"
#include <stdio.h>

#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main()
{
    // char* str = strdup("Это неизвестно кто");
    // Node_t* n1 = Make_Node(str);

    Node_t* n2 = Read_Tree();

    if (n2 == NULL)
    {
        fprintf(stderr, "Read_Tree returned NULL\n");
        return 1;
    }

    // Definition(n2, "Саша Мартынов");
    Comparator(n2, "Дима Тюлькин", "Артем");

    // Definition(n2, "Дима Тюлькин");

    // while(Akinator(n2));
    
    // Print_Tree(n2);

    // FILE* fp = fopen(SAVE_TREE_FILE, "w");
    // Save_Tree(n2, fp);
    // fclose(fp);

    Tree_Destructor(n2);

    return 0;
}