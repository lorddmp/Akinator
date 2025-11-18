#include "def_and_compar.h"

void Make_Path(Node_t* node, const char* value, bool* value_not_found, char* massive, int* position)
{
    assert(node);
    (*position)++;

    if (node->left != NULL && *value_not_found)
        Make_Path(node->left, value, value_not_found, massive, position);

    if (node->right != NULL && *value_not_found)
        Make_Path(node->right, value, value_not_found, massive, position);

    if (*value_not_found && !(strcmp(node->value, value)))
        *value_not_found = false;

    if (*value_not_found == false && *position)
    {
        if (node->parent->left == node)
            massive[*position - 1] = 'L';
        else if (node->parent->right == node)
            massive[*position - 1] = 'R';
    }

    (*position)--;

}

void Help_Definition(Node_t* node, const char* massive)
{
    assert(node);

    if (massive[0] == 'L')
    {
        printf("%s, ", node->value);
        Help_Definition(node->left, &massive[1]);
    }
    else if (massive[0] == 'R')
    {
        printf("не %s, ", node->value);
        Help_Definition(node->right, &massive[1]);
    }
}

void Definition(Node_t* node, const char* value)
{
    bool value_not_found = true;
    int position = -1;
    char massive[100] = {};

    Make_Path(node, value, &value_not_found, massive, &position);

    printf("%s - ", value);

    Help_Definition(node, massive);
    printf("\b\b \n");
}

void Comparator(Node_t* node, const char* value1, const char* value2)
{
    assert(node);

    int position = -1;
    bool value_not_found = true;
    char massive1[100] = {};
    Make_Path(node, value1, &value_not_found, massive1, &position);

    value_not_found = true;
    char massive2[100] = {};
    Make_Path(node, value2, &value_not_found, massive2, &position);

    int len = 0;
    if (strlen(massive1) > strlen(massive2))
        len = (int)strlen(value2);
    else
        len = (int)strlen(value1);

    position = 0;
    for (; strncmp(massive1, massive2, (size_t)(position + 1)) == 0 && position < len; position++);

    if (position == len)
        printf("Absolute same!\n");
    else
    {
        for (int i = 0; i < position; i++)
        {
            if (massive1[i] == 'L')
                node = node->left;
            else
                node = node->right;
        }
        printf("%s отличается от %s тем, что ", value1, value2);
        Definition(node, value1);
    }
}