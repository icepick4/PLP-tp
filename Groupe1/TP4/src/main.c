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


char *stringToPostFix(char *expression, int length) {
  char *result = malloc(length * sizeof(char));

  struct liste pileOperateur;
  pileOperateur.premier.suivant = &pileOperateur.dernier;
  pileOperateur.dernier.precedent = &pileOperateur.premier;
  pileOperateur.dernier.suivant = NULL;
  pileOperateur.premier.precedent = NULL;

  int resultIndex = 0;

  for (int i = 0; i < length; i++) {
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
        struct element *elem = pileOperateur.dernier.precedent;
        while (precedence(expression[i]) <= precedence(elem->operateur)) {
          // Dépiler et ajouter au résultat
          result[resultIndex] = elem->operateur;
          resultIndex++;
          elem = elem->precedent;
          depiler(&pileOperateur);
        }
        struct element *nouveau = malloc(sizeof(struct element));
        nouveau->operateur = expression[i];
        insertion_apres(elem, nouveau);
      }
    } else if (expression[i] == '(') {
      struct element *nouveau = malloc(sizeof(struct element));
      nouveau->operateur = expression[i];
      insertion_fin(&pileOperateur, nouveau);
    } else if (expression[i] == ')') {
      struct element *elem = pileOperateur.dernier.precedent;
      while (elem->operateur != '(') {
        result[resultIndex] = elem->operateur;
        resultIndex++;
        elem = elem->precedent;
        depiler(&pileOperateur);
      }
      depiler(&pileOperateur);
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
  char *expression = "3 + 4 * (5 - 2) / 3";
  const int length = 19;
  char *result = stringToPostFix(expression, length);
  printf("%s\n", result);
  free(result);
  return 0;
}
