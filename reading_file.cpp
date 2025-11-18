#include "reading_tree.h"
#include "technic_func.h"

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
    Skip_Spaces(position, massive);

    if (massive[*position] == '(')
    {
        Node_t* node = Obrabotka_Node(position, massive);
        IF_ERROR(node);
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

Node_t* Obrabotka_Node(int* position, char* massive)
{
    int num = 0;

    char* new_value = (char*)calloc(100, sizeof(char));
    IF_ERROR(new_value);

    Node_t* node = Make_Node(NULL);

    (*position)++;
    Skip_Spaces(position, massive);
    sscanf(&massive[*position], "\"%[^\"]\"%n", new_value, &num);
    if (num == 0)
    {
        fprintf(stderr, "ERROR in file: %s,\nfunction: %s,\n line: %d", __FILE__, __func__, __LINE__);  \
        return NULL;
    }

    node->value = new_value;
    (*position) += num;
    Skip_Spaces(position, massive);

    if((node->left = Read_Node(position, massive)) != NULL)
        node->left->parent = node;
    if((node->right = Read_Node(position, massive)) != NULL)
        node->right->parent = node;
    Skip_Spaces(position, massive);

    (*position)++;
    return node;
}