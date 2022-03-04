#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

/**
 * @brief Lit un caractère avec sécurité
 * 
 * @return char le caractère lu
 */
char lireCaractere()
{
    char caractere = toupper(getchar());

    while (getchar() != '\n') ; // Vider le buffer, ne tenir compte que le premier char saisi
    return caractere;
}

/**
 * @brief Initialise un tableau d'entier par un entier spécifié
 * 
 * @param tailleTableau la taille du tableau
 * @param tableau l'adresse du tableau
 * @param valeur la valeur qui sera initiale
 */
void initIntTab(int tailleTableau, int tableau[], int valeur)
{
    int i;
    for(i = 0; i < tailleTableau; i++)
    {
        tableau[i] = valeur;
    }
}