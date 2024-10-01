#include <stdio.h>
#include "evaluation.h"

float evaluer(struct Expression expression)
{
    if (expression.operation[0] == '+')
    {
        return expression.operand1 + expression.operand2;
    }
    else if (expression.operation[0] == '-')
    {
        return expression.operand1 - expression.operand2;
    }
    else if (expression.operation[0] == '*')
    {
        return expression.operand1 * expression.operand2;
    }
    else if (expression.operation[0] == '/')
    {
        return expression.operand1 / expression.operand2;
    }
    return 0;
}