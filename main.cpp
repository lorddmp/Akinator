#include "tree.h"
#include <stdio.h>

int main()
{
    bool a = 1;
    Node_t* n1 = Make_Node("Это неизвестно кто"); //?

    while(a)
        a = Akinator(n1);
    
    Print_Tree(n1);

    Tree_Destructor(n1);

    return 0;
}