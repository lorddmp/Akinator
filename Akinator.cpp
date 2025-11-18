#include "Akinator.h"
#include "technic_func.h"

bool Akinator(Node_t* node)
{
    assert(node);

    node = Asking_Questions(node);
    IF_ERROR(node);

    IF_ERROR(Is_Object_Right(node));

    printf("Would you like to continue?\n");

    return Get_Answer();
}

Node_t* Asking_Questions(Node_t* node)
{
    assert(node);

    printf(SPEC "?\n", node->value);

    while (node->left != NULL && node->right != NULL)
    {
        if (Get_Answer())
            node = node->left;
        else
            node = node->right;

        printf(SPEC "?\n", node->value);
    }

    return node;
}

int Get_Answer(void)
{
    char choose[100] = {};

    while(1)
    {
        scanf("%s", choose);
        Clean_Buffer();

        if (strcmp(choose, "yes") == 0)
            return 1;
        else if (strcmp(choose, "no") == 0)
            return 0;
        else 
            fprintf(stderr, "Wrong answer. Choose between yes/no: ");
    }
}

Node_t* Is_Object_Right(Node_t* node)
{
    assert(node);

    if (Get_Answer())
        printf("Ha, Dima has written this perfect code\n");
    else
    {
        char* new_value = (char*)calloc(100, sizeof(char));
        IF_ERROR(new_value);

        char* new_quest = (char*)calloc(100, sizeof(char));
        IF_ERROR(new_quest);
        
        printf("Oops, please write, what did you guess: ");
        scanf("%[^\n]", new_value);
        Clean_Buffer();

        node->left = Make_Node(new_value);
        node->left->parent = node;
        node->right = Make_Node(node->value);
        node->right->parent = node;

        printf("Please write a difference between my variant and yours: ");
        scanf("%[^\n]", new_quest);
        Clean_Buffer();

        node->value = new_quest;
    }
    return node;
}