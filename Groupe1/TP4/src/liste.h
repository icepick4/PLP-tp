#ifndef LISTE_H
#define LISTE_H

struct element {
    char operateur;
    double valeur;
    struct element *suivant;
    struct element *precedent;
};

struct liste {
    struct element premier;
    struct element dernier;
};

void insertion_debut(struct liste *, struct element *);

void insertion_fin(struct liste *, struct element *);

void insertion_apres(struct element *, struct element *);

void parcourir_debut(struct liste *);

void parcourir_fin(struct liste *);

void afficher_valeur(struct liste *);

int est_vide(struct liste *);

struct element *depiler(struct liste *);

void liberer_liste(struct liste *);

#endif // LISTE_H
