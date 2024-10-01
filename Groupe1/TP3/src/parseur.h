#ifndef PARSEUR_H
#define PARSEUR_H

#include <stdio.h>

struct Expression
{
    char *operation;
    float operand1;
    float operand2;
};

struct Expression parseur(char **tokens);

#endif // PARSEUR_H
