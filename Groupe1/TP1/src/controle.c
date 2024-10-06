#include <stdio.h>

/**
 * Author:    Rémi Jara
 * Objective: Afficher les nombres modulo 4 et pas 6, modulo 2 et 8, modulo 5 ou 7 et pas 10
 * Created:   16/09/2024
 *
 **/

int main() {
    for (int i = 1; i < 1001; i++) {
        if (i % 4 == 0 && i % 6 != 0) {
            printf("%d\n", i);
        }

        if (i % 2 == 0 && i % 8 == 0) {
            printf("%d\n", i);
        }

        if ((i % 5 == 0 || i % 7 == 0) && i % 10 != 0) {
            printf("%d\n", i);
        }
    }

    return 0;
}
