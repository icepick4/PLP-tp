#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "liste.h"
#include "evaluer.h"

#define MAX_VARIABLES 100

typedef enum
{
    ENTIER,
    REEL,
    CHAINE
} Type;

typedef struct
{
    char nom[100];
    Type type;
    union
    {
        int entier;
        double reel;
        char chaine[100];
    } valeur;
} Variable;

Variable variables[MAX_VARIABLES];
int nbVariables = 0;

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

Variable *trouverVariable(char *nom)
{
    for (int i = 0; i < nbVariables; i++)
    {
        if (strcmp(variables[i].nom, nom) == 0)
        {
            return &variables[i];
        }
    }
    return NULL;
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
        else if (isalpha(expression[i]))
        {
            char varName[100];
            int varIndex = 0;
            while (i < length && (isalpha(expression[i]) || isdigit(expression[i])))
            {
                varName[varIndex++] = expression[i++];
            }
            varName[varIndex] = '\0';
            i--;

            Variable *var = trouverVariable(varName);
            if (var != NULL)
            {
                char varValue[100];
                switch (var->type)
                {
                case ENTIER:
                    sprintf(varValue, "%d", var->valeur.entier);
                    break;
                case REEL:
                    sprintf(varValue, "%f", var->valeur.reel);
                    break;
                case CHAINE:
                    strcpy(varValue, var->valeur.chaine);
                    break;
                }
                for (int j = 0; j < strlen(varValue); j++)
                {
                    result[resultIndex++] = varValue[j];
                }
            }
            else
            {
                printf("Erreur : Variable %s non définie\n", varName);
                liberer_liste(&pileOperateur);

                return "\0";
            }
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

void ajouterVariable(char *nom, Type type, void *valeur)
{
    Variable *var = trouverVariable(nom);
    if (var == NULL)
    {
        var = &variables[nbVariables++];
        strcpy(var->nom, nom);
        var->type = type;
    }
    if (var->type != type)
    {
        printf("Erreur : Changement de type non autorisé pour la variable %s\n", nom);
        return;
    }
    switch (type)
    {
    case ENTIER:
        var->valeur.entier = *(int *)valeur;
        break;
    case REEL:
        var->valeur.reel = *(double *)valeur;
        break;
    case CHAINE:
        strcpy(var->valeur.chaine, (char *)valeur);
        break;
    }
}

char **splitNameAndValueFromCommand(char *commande)
{
    char **result = malloc(2 * sizeof(char *));
    char nom[100];
    char valeur[100];
    int i = 0;
    while (commande[i] != '=')
    {
        nom[i] = commande[i];
        i++;
    }
    nom[i] = '\0';
    i++;
    int j = 0;
    while (commande[i] != '\0')
    {
        valeur[j] = commande[i];
        i++;
        j++;
    }
    valeur[j] = '\0';
    result[0] = nom;
    result[1] = valeur;
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
        // Remove spaces
        for (int i = 0; i < strlen(commande); i++)
        {
            if (commande[i] == ' ')
            {
                for (int j = i; j < strlen(commande); j++)
                {
                    commande[j] = commande[j + 1];
                }
            }
        }
        if (commande[0] == 'q')
        {
            quitter = 1;
        }
        else if (strstr(commande, "=") != NULL)
        {
            char nom[100];
            char valeur[100];
            printf("Commande : %s\n", commande);
            char **nameAndValue = splitNameAndValueFromCommand(commande);
            strcpy(nom, nameAndValue[0]);
            strcpy(valeur, nameAndValue[1]);
            if (strchr(valeur, '.') != NULL)
            {
                double val = atof(valeur);
                ajouterVariable(nom, REEL, &val);
            }
            else if (isdigit(valeur[0]))
            {
                int val = atoi(valeur);
                ajouterVariable(nom, ENTIER, &val);
            }
            else
            {
                ajouterVariable(nom, CHAINE, valeur);
            }
        }
        else
        {
            const int length = strlen(commande);
            char *result = stringToPostFix(commande, length);

            const int newLength = strlen(result);
            double resultOperation = 0;
            resultOperation = evaluerExpression(result, newLength);

            if (strcmp(result, "\0") != 0)
            {
                printf("%f\n", resultOperation);
            }
            else
            {
                printf("Erreur lors de l'évaluation de l'expression\n");
            }
        }
    }

    return 0;
}
