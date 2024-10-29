/**
 * Authors:   Rémi Jara & Matéo Guenot
 * Objective: Evaluer une expression en notation postfixée
 * Created:   14/10/2024
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "liste.h"
#include "evaluer.h"

int precedence(char operator)
{
    if (operator== '+' || operator== '-')
    {
        return 1;
    }
    else if (operator== '*' || operator== '/')
    {
        return 2;
    }
    return 0;
}

char *stringToPostFix(char *expression, int length)
{
    char *result = malloc(length * sizeof(char));

    struct liste pileOperateur;
    pileOperateur.premier.suivant = &pileOperateur.dernier;
    pileOperateur.dernier.precedent = &pileOperateur.premier;
    pileOperateur.dernier.suivant = NULL;
    pileOperateur.premier.precedent = NULL;

    int resultIndex = 0;

    for (int i = 0; i < length; i++)
    {
        if (isdigit(expression[i]))
        {
            result[resultIndex] = expression[i];
            resultIndex++;
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
        {
            if (est_vide(&pileOperateur) ||
                precedence(expression[i]) > precedence(pileOperateur.dernier.precedent->operateur))
            {
                struct element *nouveau = malloc(sizeof(struct element));
                nouveau->operateur = expression[i];
                insertion_fin(&pileOperateur, nouveau);
            }
            else
            {
                struct element *elem = pileOperateur.dernier.precedent;
                while (precedence(expression[i]) <= precedence(elem->operateur))
                {
                    result[resultIndex] = elem->operateur;
                    resultIndex++;
                    elem = elem->precedent;
                    depiler(&pileOperateur);
                }
                struct element *nouveau = malloc(sizeof(struct element));
                nouveau->operateur = expression[i];
                insertion_apres(elem, nouveau);
            }
        }
        else if (expression[i] == '(')
        {
            struct element *nouveau = malloc(sizeof(struct element));
            nouveau->operateur = expression[i];
            insertion_fin(&pileOperateur, nouveau);
        }
        else if (expression[i] == ')')
        {
            struct element *elem = pileOperateur.dernier.precedent;
            while (elem->operateur != '(')
            {
                result[resultIndex] = elem->operateur;
                resultIndex++;
                elem = elem->precedent;
                depiler(&pileOperateur);
            }
            depiler(&pileOperateur);
            free(elem);
        }
    }

    while (!est_vide(&pileOperateur))
    {
        struct element *elem = pileOperateur.dernier.precedent;
        result[resultIndex] = elem->operateur;
        resultIndex++;
        depiler(&pileOperateur);
        free(elem);
    }

    liberer_liste(&pileOperateur);

    result[resultIndex] = '\0';

    return result;
}

int main()
{
    printf("Entrez l'expression de votre choix.\n Tapez q pour quitter.\n");
    char commande[100];

    int quitter = 0;
    while (!quitter)
    {
        printf(">");
        fgets(commande, 100, stdin);
        if (commande[0] == 'q')
        {
            quitter = 1;
        }
        else
        {
            const int length = strlen(commande);
            char *result = stringToPostFix(commande, length);

            const int newLength = strlen(result);
            double resultOperation = 0;
            resultOperation = evaluerExpression(result, newLength);

            printf("%f\n", resultOperation);
            free(result);
        }
    }

    return 0;
}
