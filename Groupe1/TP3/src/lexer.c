/**
 * Authors:   Rémi Jara & Matéo Guenot
 * Objective: Tokeniser une expression
 * Created:   1/10/2024
 *
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **lexer(char *expression)
{
    int expression_length = strlen(expression);
    char **tokens = malloc((expression_length + 1) * sizeof(char *));
    int i = 0;

    for (int j = 0; j < expression_length; j++)
    {
        if (expression[j] == ' ')
        {
            continue;
        }
        tokens[i] = malloc(2 * sizeof(char));
        tokens[i][0] = expression[j];
        tokens[i][1] = '\0';
        i++;
    }
    tokens[i] = NULL;

    // Check for syntax error (operator in first or last position)
    if (tokens[0][0] == '+' || tokens[0][0] == '-' || tokens[0][0] == '*' || tokens[0][0] == '/')
    {
        printf("Syntax error: operator in first position\n");
        return NULL;
    }
    else if (tokens[i - 1][0] == '+' || tokens[i - 1][0] == '-' || tokens[i - 1][0] == '*' || tokens[i - 1][0] == '/')
    {
        printf("Syntax error: operator in last position\n");
        return NULL;
    }

    return tokens;
}