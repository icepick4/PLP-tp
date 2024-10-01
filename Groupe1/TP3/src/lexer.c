#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **lexer(char *expression)
{
    int expression_length = strlen(expression);
    char **tokens = malloc(expression_length * sizeof(char *));
    char *str = malloc(expression_length * sizeof(char));
    str = strcpy(str, expression);
    char *token = strtok(str, " ");
    int i = 0;
    while (token != NULL)
    {
        // is float or int
        if (atof(token) != 0 || token[0] == '0')
        {
            printf("float: %f\n", atof(token));
            tokens[i] = token;
        }
        else
        {
            // is operator
            printf("operator: %c\n", token[0]);
            if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
            {
                tokens[i] = token;
            }
        }

        tokens[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    // check for syntax error (operator in first or last position)
    if (tokens[i - 1][0] == '+' || tokens[i - 1][0] == '-' || tokens[i - 1][0] == '*' || tokens[i - 1][0] == '/')
    {
        printf("Syntax error: operator in last position\n");
        return NULL;
    }
    else if (tokens[0][0] == '+' || tokens[0][0] == '-' || tokens[0][0] == '*' || tokens[0][0] == '/')
    {
        printf("Syntax error: operator in first position\n");
        return NULL;
    }
    return tokens;
}