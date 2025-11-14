#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>

#define DUMP_TREE_FILE "Tree_Dump.txt"

#define IF_ERROR(arg)                                                                                   \
do {                                                                                                    \
    if (arg == NULL)                                                                                    \
    {                                                                                                   \
        fprintf(stderr, "ERROR in file: %s,\nfunction: %s,\n line: %d", __FILE__, __func__, __LINE__);  \
        return NULL;                                                                                    \
    }                                                                                                   \
} while (0)

Node_t* Read_Tree(void)
{ 
    FILE* fp = fopen(SAVE_TREE_FILE, "r");
    struct stat stat1 = {};
    int descriptor = fileno(fp);
    int position = 0;
    
    fstat(descriptor, &stat1);

    char* massive = (char*)calloc((size_t)stat1.st_size + 1, sizeof(char));
    IF_ERROR(massive);

    fread(massive, sizeof(char), (size_t)stat1.st_size, fp);

    Node_t* node = Read_Node(&position, massive);
    IF_ERROR(node);

    free(massive);
    fclose(fp);

    return(node);
}

Node_t* Read_Node(int* position, char* massive)
{
    int num = 0;
    Skip_Spaces(position, massive);

    if (massive[*position] == '(')
    {
        char* new_value = (char*)calloc(100, sizeof(char));
        IF_ERROR(new_value);
        Node_t* node = Make_Node(NULL);
        (*position)++;
        Skip_Spaces(position, massive);
        sscanf(&massive[*position], "\"%[^\"]\"%n", new_value, &num); //aaaaaaaaaaaaaaa
        node->value = new_value;
        (*position) += num;
        Skip_Spaces(position, massive);
        node->left = Read_Node(position, massive);
        node->right = Read_Node(position, massive);
        Skip_Spaces(position, massive);
        (*position)++;
        return node;
    }

    if (!(strncmp(&massive[*position], "nil", 3)))
    {
        *position += 3;
        return NULL;
    }
    else
    {
        printf("Error in reading file\n");
        return NULL;
    }
}

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
            printf("Wrong answer. Choose between yes/no: ");
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
        node->right = Make_Node(node->value);

        printf("Please write a difference between my variant and yours: ");
        scanf("%[^\n]", new_quest);
        Clean_Buffer();

        node->value = new_quest;
    }
    return node;
}

void Save_Tree(Node_t* node, FILE* fp)
{
    assert(node);
    fprintf(fp, "( ");
    fprintf(fp, "\"%s\" ", node->value);

    if (node->left != NULL)
        Save_Tree(node->left, fp);
    else
        fprintf(fp, "nil ");

    if (node->right != NULL)
        Save_Tree(node->right, fp);
    else
        fprintf(fp, "nil ");

    fprintf(fp, ") ");
}

void Print_Node(Node_t* node, FILE* fp)
{
    assert(node);
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
    assert(node);
    FILE* fp = fopen(DUMP_TREE_FILE, "w");

    if (fp == NULL)
        fprintf(stderr, "ERROR IN OPENING DUMP FILE\n");

    fprintf(fp, "Digraph G{\n");
    Print_Node(node, fp);
    fprintf(fp, "}");

    fclose(fp);
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