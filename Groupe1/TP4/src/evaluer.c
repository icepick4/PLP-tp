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
            nouveau->valeur = (double) (expression[i] - '0');
            printf("Nouveau chiffre : %f\n", nouveau->valeur);
            insertion_fin(&pileOperateur, nouveau);
        } else {
            printf("La pile : ");
            afficher_valeur(&pileOperateur);
            struct element operande1 = depiler(&pileOperateur);
            struct element operande2 = depiler(&pileOperateur);
            double resultNumber = 0;

            printf("Opérande 1 : %f\n", operande1.valeur);
            printf("Opérande 2 : %f\n", operande2.valeur);
            switch (expression[i]) {
                case '+':
                    resultNumber = operande1.valeur + operande2.valeur;
                    break;
                case '-':
                    resultNumber = operande2.valeur - operande1.valeur;
                    break;
                case '/':
                    resultNumber = operande2.valeur / operande1.valeur;
                    break;
                case '*':
                    resultNumber = operande1.valeur * operande2.valeur;
                    break;
                default:
                    printf("Erreur ! L'expression %c n'est pas définie", expression[i]);
                    resultNumber = 0;
                    break;
            }

            printf("Résulat de l'opération %f %c %f : %f\n", operande2.valeur, expression[i], operande1.valeur,
                   resultNumber);

            struct element *nouveau = malloc(sizeof(struct element));
            nouveau->valeur = resultNumber;
            printf("Element à insérer : %f\n", nouveau->valeur);
            insertion_fin(&pileOperateur, nouveau);
        }
    }

    return pileOperateur.premier.suivant->valeur;
}
