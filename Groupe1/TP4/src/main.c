#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // <cctype> en C++

#include "liste.h"

int precedence(char operator) {
  if (operator == '+' || operator == '-') {
    return 1;
  } else if (operator == '*' || operator == '/') {
    return 2;
  }
  return 0;
}


// expression = "3 + 4 * 5"
// output = "3 4 5 * +"
char *stringToPostFix(char *expression, int length) {
  char *result = malloc(length * sizeof(char));

  struct liste pileOperateur;
  pileOperateur.premier.suivant = &pileOperateur.dernier;
  pileOperateur.dernier.precedent = &pileOperateur.premier;
  pileOperateur.dernier.suivant = NULL;
  pileOperateur.premier.precedent = NULL;

  int resultIndex = 0;

  for (int i = 0; i < length; i++) {
    printf("Result : %s\n", result);
    printf("Opérateurs : \n");
    parcourir_debut(&pileOperateur);
    if (isdigit(expression[i])) {
      result[resultIndex] = expression[i];
      resultIndex++;
    } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
      if (est_vide(&pileOperateur) ||
          precedence(expression[i]) > precedence(pileOperateur.dernier.precedent->operateur)) {
        struct element *nouveau = malloc(sizeof(struct element));
        nouveau->operateur = expression[i];
        insertion_fin(&pileOperateur, nouveau);
      } else {
        printf("La pile n'est pas vide\n");
        struct element *elem = pileOperateur.dernier.precedent;
        printf("Dernier operateur de la pile : %c\n", elem->operateur);
        printf("Est ce que %c est plus petit ou égal à %c\n", expression[i], elem->operateur);
        while (precedence(expression[i]) <= precedence(elem->operateur)) {
          // Dépiler et ajouter au résultat
          result[resultIndex] = elem->operateur;
          resultIndex++;
          printf("%c est plus petit ou égal à %c donc on ajoute %c au résultat final\n", expression[i],
                 elem->operateur, elem->operateur);
          elem = elem->precedent;
          depiler(&pileOperateur);
        }
        struct element *nouveau = malloc(sizeof(struct element));
        nouveau->operateur = expression[i];
        printf("On ajoute %c à la pile après %c\n", nouveau->operateur, elem->operateur);
        insertion_apres(elem, nouveau);
        printf("Pile à l'étape %d\n", i);
      }
    }
  }


  // on dépile tous les opérateurs restants
  while (!est_vide(&pileOperateur)) {
    struct element *elem = pileOperateur.dernier.precedent;
    result[resultIndex] = elem->operateur;
    resultIndex++;
    depiler(&pileOperateur);
  }

  return result;
}

int main() {
  char *expression = "3 + 4 * 5 - 2 / 3";
  const int length = 17;
  char *result = stringToPostFix(expression, length);
  printf("%s\n", result);
  free(result);
  return 0;
}
