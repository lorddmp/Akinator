#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void Print_Node(Node_t* node, FILE* fp)
{
    fprintf(fp, "node%p [shape = record, label=\"{" SPEC "? | {<f0> да| <f1> нет}}\"];\n", node, node->value);

    if (node->left != NULL)
    {
        Print_Node(node->left, fp);
        fprintf(fp, "node%p:<f0>->node%p;\n", node, node->left);
    }
    if (node->right != NULL)
    {
        Print_Node(node->right, fp);
        fprintf(fp, "node%p:<f1>->node%p;\n", node, node->right);
    }
}

void Print_Tree(Node_t* node)
{
    FILE* fp = fopen("Tree_Dump.txt", "w");

    fprintf(fp, "Digraph G{\n");//доп функция для печати Print_Tree
    Print_Node(node, fp);
    fprintf(fp, "}");

    fclose(fp);
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
        Node_t* new_node = Make_Node(new_value, NULL, NULL);

        Node_t** var = (new_value < node->value) ? &node->left : &node->right;

        *var = new_node;
    }
}

Node_t* Make_Node(TreeElem_t value, Node_t* n1, Node_t* n2)
{
    Node_t* new_node = (Node_t*)calloc(1, sizeof(Node_t));

    if (new_node == NULL)
    {
        fprintf(stderr, "CALLOC ERROR\n");
        return NULL;
    }

    *new_node = {
        .value = value,
        .left = n1,
        .right = n2
    };

    return new_node;
}

void Tree_Destructor(Node_t* node)
{
    if (node->left != NULL)
        Tree_Destructor(node->left);

    if (node->right != NULL)
        Tree_Destructor(node->right);

    free(node);
}

void Delete_Node(TreeElem_t bad_value, Node_t* node)
{
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

bool Akinator(Node_t* node)
{
    char* choose = (char*)calloc(4, sizeof(char));
    int choose_from_func = 0;

    if (choose == NULL)
    {
        fprintf(stderr, "CALLOC ERROR\n");
        return NULL;
    }

    char* new_value = (char*)calloc(100, sizeof(char));

    if (new_value == NULL)
    {
        fprintf(stderr, "CALLOC ERROR\n");
        return NULL;
    }

    char* new_quest = (char*)calloc(100, sizeof(char));

    if (new_quest == NULL)
    {
        fprintf(stderr, "CALLOC ERROR\n");
        return NULL;
    }

    printf(SPEC "?\n", node->value);

    while (node->left != NULL)
    {
        scanf("%s", choose);
        choose_from_func = Get_Answer(choose);
        Clean_Buffer();

        if (choose_from_func == 1)
            node = node->left;
        else if (choose_from_func == 0)
            node = node->right;
        else
        {
            printf("Wrong answer. Try again\n");
            continue;
        }

        printf(SPEC "?\n", node->value);
    }

    while(1)
    {
    scanf("%s", choose);
    choose_from_func = Get_Answer(choose);
    Clean_Buffer();

    if (choose_from_func == 1)
    {
        printf("Ha, Dima has written this perfect code\n");
        break;
    }
    else if (choose_from_func == 0)
    {
        printf("Oops, please write, what did you guess: ");
        scanf("%[^\n]", new_value);
        Clean_Buffer();

        node->left = Make_Node(new_value, NULL, NULL);
        node->right = Make_Node(node->value, NULL, NULL);

        printf("Please write a difference between my variant and yours: ");
        scanf("%[^\n]", new_quest);
        Clean_Buffer();

        node->value = new_quest;
        break;
    }
    else
        printf("Wrong answer. Try again\n");
    }

    printf("Would you like to continue?\n");
    scanf("%s", choose);
    choose_from_func = Get_Answer(choose);
    Clean_Buffer();

    free(choose);
    free(new_value);
    free(new_quest);

    return choose_from_func == 1 ? 1 : 0;
}

void Clean_Buffer(void)
{
    while(getchar() != '\n');
}

bool Get_Answer(char* choose)
{
    if (strcmp(choose, "yes") == 0)
        return 1;
    else if (strcmp(choose, "no") == 0)
        return 0;
    else 
        return -1;
}