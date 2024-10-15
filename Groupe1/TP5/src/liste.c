#include "liste.h"

#include <stdio.h>
#include <stdlib.h>

void insertion_debut(struct liste *liste, struct element *nouveau)
{
    nouveau->suivant = liste->premier.suivant;
    nouveau->precedent = &liste->premier;
    liste->premier.suivant->precedent = nouveau;
    liste->premier.suivant = nouveau;
}

void insertion_fin(struct liste *liste, struct element *nouveau)
{
    nouveau->suivant = &liste->dernier;
    nouveau->precedent = liste->dernier.precedent;
    liste->dernier.precedent->suivant = nouveau;
    liste->dernier.precedent = nouveau;
}

void insertion_apres(struct element *elem, struct element *nouveau)
{
    nouveau->suivant = elem->suivant;
    nouveau->precedent = elem;
    elem->suivant->precedent = nouveau;
    elem->suivant = nouveau;
}

void parcourir_debut(struct liste *liste)
{
    struct element *elem = liste->premier.suivant;
    while (elem != &liste->dernier)
    {
        printf("%c\n", elem->operateur);
        elem = elem->suivant;
    }
}

void parcourir_fin(struct liste *liste)
{
    struct element *elem = liste->dernier.precedent;
    while (elem != &liste->premier)
    {
        printf("%c\n", elem->operateur);
        elem = elem->precedent;
    }
}

void afficher_valeur(struct liste *liste)
{
    struct element *elem = liste->premier.suivant;
    while (elem != &liste->dernier)
    {
        printf("%f\n", elem->valeur);
        elem = elem->suivant;
    }
}

int est_vide(struct liste *liste)
{
    return liste->premier.suivant == &liste->dernier;
}

struct element *depiler(struct liste *liste)
{
    if (est_vide(liste))
    {
        printf("La pile est vide\n");
        return NULL;
    }

    struct element *elem = liste->dernier.precedent;
    liste->dernier.precedent = elem->precedent;
    elem->precedent->suivant = &liste->dernier;

    return elem;
}

void liberer_liste(struct liste *liste)
{
    struct element *elem = liste->premier.suivant;
    while (elem != &liste->dernier)
    {
        struct element *temp = elem;
        elem = elem->suivant;
        free(temp);
    }
    liste->premier.suivant = &liste->dernier;
    liste->dernier.precedent = &liste->premier;
}
