#include <stdio.h>
#include <stdlib.h>
#include "parseur.h"

struct Expression parseur(char **tokens)
{
    struct Expression expression;
    int i = 0;
    while (tokens[i] != NULL)
    {
        if (tokens[i][0] == '+' || tokens[i][0] == '-' || tokens[i][0] == '*' || tokens[i][0] == '/')
        {
            expression.operation = tokens[i];
            expression.operand1 = atof(tokens[i - 1]);
            expression.operand2 = atof(tokens[i + 1]);
        }
        i++;
    }
    return expression;
}