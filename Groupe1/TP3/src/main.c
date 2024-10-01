#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"

int main()
{
    char expression[100];
    printf("Enter an expression: ");
    scanf("%[^\n]s", expression);
    char **tokens = lexer(expression);
    struct Expression expression_struct = parseur(tokens);
    float result = evaluer(expression_struct);
    printf("Result: %f\n", result);
    return 0;
}