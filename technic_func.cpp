#include "technic_func.h"

Node_t* Make_Node(TreeElem_t value, Node_t* n1, Node_t* n2)
{
    Node_t* new_node = (Node_t*)calloc(1, sizeof(Node_t));
    IF_ERROR(new_node);

    *new_node = {
        .value = value,
        .left = n1,
        .right = n2
    };

    return new_node;
}

void In_Node(TreeElem_t new_value, Node_t* node)
{
    assert(node);

    if (new_value < node->value && node->left != NULL)
        In_Node(new_value, node->left);
    else if (new_value >= node->value && node->right != NULL)
        In_Node(new_value, node->right);
    else
    {
        Node_t* new_node = Make_Node(new_value);

        Node_t** var = (new_value < node->value) ? &node->left : &node->right;

        *var = new_node;
    }
}

void Delete_Node(TreeElem_t bad_value, Node_t* node)
{
    assert(node);

    if (node->value == bad_value)
        Tree_Destructor(node);
    else if (node->left != NULL && node->left->value == bad_value)
    {
        Tree_Destructor(node->left);
        node->left = NULL;
    }
    else if (node->right != NULL && node->right->value == bad_value)
    {
        Tree_Destructor(node->right);
        node->right = NULL;
    }
    else
    {
        Node_t* var = (bad_value < node->value) ? node->left : node->right;
        Delete_Node(bad_value, var);
    }
}

void Tree_Destructor(Node_t* node)
{
    assert(node);
    if (node->left != NULL)
        Tree_Destructor(node->left);

    if (node->right != NULL)
        Tree_Destructor(node->right);

    free(node->value);
    free(node);
}

void Clean_Buffer(void)
{
    while(getchar() != '\n');
}

void Skip_Spaces(int* position, char* massive)
{
    assert(massive);
    while (massive[*position] == ' ')
        (*position)++;
}