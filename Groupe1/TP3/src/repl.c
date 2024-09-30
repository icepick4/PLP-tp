#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Variables globales
int VAR_VERSION = 1;

// Déclaration des fonctions
void afficher_version();

void afficher_help();

void traiter_echo(char *commande);

void traiter_quit(int *continuer);

void traiter_date();

// Enum pour spécifier le type de fonction
enum FUNCTION_TYPE {
    NO_PARAM,
    CHAR_PTR_PARAM,
    INT_PTR_PARAM
};

// Structure modifiée pour accepter des fonctions avec des signatures différentes
struct COMMANDE {
    char *name;
    enum FUNCTION_TYPE type;

    void (*function)();
};

// Tableau de commandes
struct COMMANDE commandes[] = {
    {"echo", CHAR_PTR_PARAM, (void (*)()) traiter_echo},
    {"afficher", CHAR_PTR_PARAM, (void (*)()) traiter_echo},
    {"quit", INT_PTR_PARAM, (void (*)()) traiter_quit},
    {"quitter", INT_PTR_PARAM, (void (*)()) traiter_quit},
    {"date", NO_PARAM, (void (*)()) traiter_date},
    {"version", NO_PARAM, (void (*)()) afficher_version},
    {"help", NO_PARAM, (void (*)()) afficher_help},
    {"aide", NO_PARAM, (void (*)()) afficher_help},
};

int min(int a, int b) {
    return (a < b) ? a : b;
}

// Fonction de calcul de la distance de Levenshtein
int levenshtein(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int matrix[len2 + 1][len1 + 1];
    for (int x = 0; x <= len2; x++) matrix[x][0] = x;
    for (int y = 0; y <= len1; y++) matrix[0][y] = y;
    for (int x = 1; x <= len2; x++) {
        for (int y = 1; y <= len1; y++) {
            int cost = (s1[y - 1] == s2[x - 1]) ? 0 : 1;
            matrix[x][y] = min(min(matrix[x - 1][y] + 1, matrix[x][y - 1] + 1), matrix[x - 1][y - 1] + cost);
        }
    }
    return matrix[len2][len1];
}

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

int main() {
    int continuer = 1; // Variable pour contrôler la boucle principale

    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer) {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];

        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        // Traite la commande en fonction de son contenu
        int commande_traitee = 0;
        int min_distance = 3; // Seuil de distance minimale pour une correction
        char *suggestion = NULL;

        for (int i = 0; i < sizeof(commandes) / sizeof(commandes[0]); i++) {
            // Calcul de la distance de Levenshtein entre la commande et les commandes valides
            int distance = levenshtein(commandes[i].name, commande);
            if (distance == 0) {
                // Si la commande correspond exactement, on l'exécute
                switch (commandes[i].type) {
                    case NO_PARAM:
                        ((void (*)()) commandes[i].function)();
                        break;
                    case CHAR_PTR_PARAM:
                        ((void (*)(char *)) commandes[i].function)(commande);
                        break;
                    case INT_PTR_PARAM:
                        ((void (*)(int *)) commandes[i].function)(&continuer);
                        break;
                }
                commande_traitee = 1;
                break;
            } else if (distance < min_distance) {
                // Si une commande similaire est trouvée, on la suggère
                min_distance = distance;
                suggestion = commandes[i].name;
            }
        }

        if (!commande_traitee) {
            if (suggestion) {
                printf("Commande inconnue. Vouliez-vous dire : '%s' ?\n", suggestion);
            } else {
                printf("Commande inconnue\n");
            }
        }

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}

void afficher_version() {
    printf("Version %d\n", VAR_VERSION);
}

void afficher_help() {
    printf("Aide : \n");
    printf("echo <text> : Affiche le texte spécifié\n");
    printf("version : Affiche la version du programme\n");
    printf("quit : Quitte le programme\n");
}

void traiter_echo(char *commande) {
    printf("Echo: %s\n", commande);
}

void traiter_quit(int *continuer) {
    printf("Arrêt...\n");
    *continuer = 0;
}

void traiter_date() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Date: %d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}
