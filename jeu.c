#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "fonctions.h"
#include "jeu.h"

/**
 * @brief Décremente le nombre de coups si la lettreEntre n'est pas dans motSecret sinon change le 0 de motTrouve en 1
 * 
 * @param lettreEntre le caractere saisi par l'utilisateur
 * @param motSecret le mot à deviner
 * @param tailleMotSecret la taille du mot à deviner
 * @param motTrouve tableau identifiant les char qui sont trouvé
 * @param nombreCoups le nombre de coups restant
 */
void decrementationCoups(int lettreEntre, char motSecret[], int tailleMotSecret, int* motTrouve, int *nombreCoups)
{
    int decrementationCoups = 1, i;

    for(i=0;i<tailleMotSecret;i++)
    {
        if(lettreEntre==motSecret[i])
        {
            motTrouve[i]=1;
            decrementationCoups = 0;
        }
    }
    
    if(decrementationCoups)
    {
        (*nombreCoups)--;
        puts("\nOops!\n");
    }
}

/**
 * @brief Vérifie si la partie est finie ou non en évaluant le nombre de coups restant ou en cherchant des 0 dans motTrouve
 * 
 * @param motTrouve tableau identifiant les char qui sont trouvé
 * @param tailleMotSecret la taille du mot à deviner
 * @param nombreCoups le nombre de coups restant
 * @return int 1 si c'est la fin, 0 sinon
 */
int finPartie(int motTrouve[], int tailleMotSecret, int nombreCoups)
{
    int fin = 1, i;
    if(nombreCoups == 0)
    {
        return 1;
    }

    for(i=0;i<tailleMotSecret;i++)
    {
        if(motTrouve[i] == 0)
        {
            fin = 0;
            break;
        }
    }
    return fin;
}

/**
 * @brief Affiche le mot secret, etoile si le char n'est pas encore trouvé, char sinon
 * 
 * @param motSecret le mot à deviner
 * @param tailleMotSecret la taille du mot à deviner
 * @param motTrouve tableau identifiant les char qui sont trouvé
 */
void afficheMotSecret(char motSecret[], int tailleMotSecret, int motTrouve[])
{
    int i;
    for(i=0;i<tailleMotSecret;i++)
    {
        if(motTrouve[i]==1)
        {
            printf("%c",motSecret[i]);
        }
        else
        {
            printf("*");
        }
    }
}

/**
 * @brief Affiche le resultat final du jeu, si le nombre de coups est 0, il a perdu
 * 
 * @param nombreCoups le nombre de coups restant
 * @param motSecret le mot à deviner
 * @param aliasNiveau l'alias du niveau si il gagne
 */
void afficheResultat(int nombreCoups, char motSecret[], char *aliasNiveau)
{
    if(nombreCoups != 0) // Rah tsy resy takaka de aseho zany oe nanjesy izy
    {
        printf("\n\nVous avez trouve le mot, c'etait bien %s!\n\n",motSecret);
        printf("\tDetails du niveau : %s\n",aliasNiveau);
    }
    else // Rah vao tsisy coup tsony de vitaina
    {
        printf("\n\nVous avez perdu! (T_T) \nLe mot secret etait %s!\n",motSecret);
    }
}

/**
 * @brief Choisit un mot au hasard depuis un fichier ou depuis un tableau défini (voir TableaumotSecret dans cette fonction)
 * 
 * @param destination l'adresse de la chaine de caractère qui recevera le mot
 * @return int la taille du mot
 */
int motAleatoire(char *destination)
{
    const char TableaumotSecret[23][7] = {"MIGNON","NULLES","CORAIL","JACOBS","RENDRE","ELEVER","ALLARD","ECHOUA","MAXIMA","RECOIS","SYDNEY","COMMET","VERRAS","CHEVET","SAINTE","NIECES","ECRITE","RENOUE","TANGER","VOYAIS","ALIENE","PLATON","CRISES"};
    FILE *file = NULL;
    long i = (rand()*10)%NOMBRE_MOT; // rand est un int ( |rand| < 32768 )

    file = fopen("dico.txt","r");
    if(file == NULL)
    {
        puts("Erreur d'ouverture de dico.txt, utilisation des mots par defaut\n");
        strcpy(destination,TableaumotSecret[rand()%23]);
        return strlen(destination);
    }
    
    while(i>0)
    {
        if(fgets(destination,MAX_LEN_MOT,file) == NULL)
        {
            printf("dico.txt est endommage, utilisation des mots par defaut\n");
            strcpy(destination,TableaumotSecret[rand()%23]);
            return strlen(destination);
        }
        i--;
    }
    
    for(i = 0; destination[i] != '\n'; i++);
    destination[i] = '\0';

    fclose(file);
    return strlen(destination);
}

/**
 * @brief Affiche le titre du programme
 * 
 */
void titre()
{
    puts("\n");
    puts("**************************************************************");
    puts("\n");
    puts("************************ - LE PENDU - ************************");
    puts("\n");
    puts("**************************************************************");
    puts("\n");
}

/**
 * @brief Affiche le menu du programme et appelle l'item voulu: jouer, reglement ou quitter
 * 
 */
void menu()
{
    puts("1. Jouer\n");
    puts("2. Reglement\n");
    puts("3. Quitter\n");
    switch (lireCaractere())
    {
        case '1':
            jeu();
            break;
        
        case '3':
            /* Quitter */
            break;
        
        default:
            reglement();
            jeu();
            break;
    }
}

/**
 * @brief Affiche le reglement du jeu
 * 
 */
void reglement()
{
    puts("\n- - - - - - - - - - - - - REGLEMENT - - - - - - - - - - - - -\n");
    puts("\tOn vous fait deviner un mot. Vous devez saisir un caractere qui est dans le mot secret jusqu'a trouver le mot secret en entier. Attention, vous etes limite a un certain nombre de coups. Si vous mettez le mauvais caractere, le nombre de coups diminue.");
    puts("\n");
    system("pause");
}

/**
 * @brief Donne les détails du niveau spécifié (alias et nombre de coups)
 * 
 * @param niveau le niveau à détailler
 * @param aliasNiveau une chaine qui contiendra l'alias du niveau
 * @param nombreCoups le nombre de coups correspondant au niveau spécifié
 */
void detailNiveau(const char niveau, char *aliasNiveau, int *nombreCoups)
{
    switch (niveau)
    {
        case '1':
            strcpy(aliasNiveau,"Certain! xD");
            *nombreCoups = 30;
            break;
        case '2':
            strcpy(aliasNiveau,"Trop facile!! B)");
            *nombreCoups = 25;
            break;
        case '3':
            strcpy(aliasNiveau,"Boff.. :)");
            *nombreCoups = 20;
            break;
        case '4':
            strcpy(aliasNiveau,"Ca peut aller... :D");
            *nombreCoups = 15;
            break;
        case '5':
            strcpy(aliasNiveau,"Ca se complique! :|");
            *nombreCoups = 10;
            break;
        case '6':
            strcpy(aliasNiveau,"Nani!!? :(");
            *nombreCoups = 5;
            break;
        case '7':
            strcpy(aliasNiveau,"Pro Max! :7");
            *nombreCoups = 3;
            break;
        case '8':
            strcpy(aliasNiveau,"Thanos (Impossible!! o_O )"); // de taille 25
            *nombreCoups = 2;
            break;
        case '9':
            strcpy(aliasNiveau,"GOD!!!!!! *0*"); // de taille 25
            *nombreCoups = 1;
            break;
    }
}

/**
 * @brief Affiche les niveaux et demande le choix de l'utilisateur
 * 
 * @param nombreCoups le nombre de coups resultant correspondant au niveau
 * @param aliasNiveau une chaine qui contiendra l'alias du niveau
 */
void niveau(int *nombreCoups, char *aliasNiveau)
{
    char choix = 0;
    char i;

    puts("\n");

    for(i = '1'; i <= '9'; i++)
    {
        detailNiveau(i,aliasNiveau,nombreCoups);
        printf("\t\t- Niveau %c : %d coups\n",i,*nombreCoups);
    }

    do
    {
        puts("\n\nVotre choix?\n");
        choix = lireCaractere();
    } while(choix > '9' || choix < '1');
    
    detailNiveau(choix,aliasNiveau,nombreCoups);
    
    printf("\n . . . . . . . . . . . . Niveau %c . . . . . . . . . . . . \n\n", choix);
}

/**
 * @brief Le déroullement du jeu, jouer une autre partie 
 * 
 */
void jeu()
{
    char lettreEntre = 0, rejoue = 0, aliasNiveau[25];;
    char motSecret[MAX_LEN_MOT];
    int motTrouve[MAX_LEN_MOT]; // exemple: L*VIN* = {1,0,1,1,1,0} 
    int nombreCoups = 0, len = 0;

    srand(time(NULL));
    
    do
    {
        system("cls");
        titre();
        niveau(&nombreCoups,aliasNiveau);
        initIntTab(MAX_LEN_MOT,motTrouve,0); // initialiser chaque element de motTrouve à 0
        len = motAleatoire(motSecret);
        while(!finPartie(motTrouve,len,nombreCoups))
        {
            printf("\n\nIl vous reste %d coups a jouer\n",nombreCoups);
            printf("Quel est le mot secret? ");
            afficheMotSecret(motSecret,len,motTrouve);
            printf("\nProposez une lettre : ");
            lettreEntre = lireCaractere();
            decrementationCoups(lettreEntre,motSecret,len,motTrouve,&nombreCoups);
        }
        afficheResultat(nombreCoups,motSecret,aliasNiveau);
        printf("\n\nVoulez-vous rejouer? Repondez 1 si oui... ");
        rejoue = lireCaractere();
    }while(rejoue == '1');
}
