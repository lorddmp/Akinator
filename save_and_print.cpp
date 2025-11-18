#include "save_and_print.h"

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
    fprintf(fp, "node%p [shape = record, color = blue, label=\"{" SPEC "? | {<f0> да| <f1> нет}}\"];\n", node, node->value);

    if (node->left != NULL)
    {
        Print_Node(node->left, fp);
        fprintf(fp, "node%p:<f0>->node%p[color = green];\n", node, node->left);
    }
    if (node->right != NULL)
    {
        Print_Node(node->right, fp);
        fprintf(fp, "node%p:<f1>->node%p[color = red];\n", node, node->right);
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