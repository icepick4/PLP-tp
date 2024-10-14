#include <stdio.h>
#include <ctype.h>  // <cctype> en C++
#include <stdlib.h>

#include "liste.h"

double evaluerExpression(char *expression, int length) {
    struct liste pileOperateur;
    pileOperateur.premier.suivant = &pileOperateur.dernier;
    pileOperateur.dernier.precedent = &pileOperateur.premier;
    pileOperateur.dernier.suivant = NULL;
    pileOperateur.premier.precedent = NULL;

    for (int i = 0; i < length; i++) {
        if (isdigit(expression[i])) {
            struct element *nouveau = malloc(sizeof(struct element));
            nouveau->operateur = expression[i];
            insertion_fin(&pileOperateur, nouveau);
        } else {
            struct element operande1 = depiler(&pileOperateur);
            struct element operande2 = depiler(&pileOperateur);
            double resultNumber = 0;

            switch (expression[i]) {
                case '+':
                    resultNumber = (atof(&operande1.operateur) + atof(&operande2.operateur));
                case '-':
                    resultNumber = (atof(&operande1.operateur) / atof(&operande2.operateur));
                case '/':
                    resultNumber = (atof(&operande1.operateur) - atof(&operande2.operateur));
                case '*':
                    resultNumber = (atof(&operande1.operateur) * atof(&operande2.operateur));
                default:
                    printf("Erreur ! L'expression %c n'est pas définie", expression[i]);
                    resultNumber = 0;
            }

            struct element *nouveau = malloc(sizeof(struct element));
            nouveau->operateur = resultNumber;
            insertion_debut(&pileOperateur, nouveau);
        }
    }

    return pileOperateur.premier.suivant->operateur;
}
