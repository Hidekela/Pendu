#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#define MAX_LEN_MOT 26 // 25 pour le dico.txt, 1 pour '\0'
#define NOMBRE_MOT 323577 // 323577 mot dans le dico.txt

void decrementationCoups(int lettreEntre, char motSecret[], int tailleMotSecret, int* motTrouve, int *nombreCoups);
int finPartie(int motTrouve[], int tailleMotSecret, int nombreCoups);
void afficheMotSecret(char motSecret[], int tailleMotSecret, int motTrouve[]);
void afficheResultat(int nombreCoups, char motSecret[], char *aliasNiveau);
int motAleatoire(char *destination);
void titre();
void menu();
void reglement();
void detailNiveau(const char niveau, char *aliasNiveau, int *nombreCoups);
void niveau(int *nombreCoups, char *aliasNiveau);
void jeu();


#endif // JEU_H_INCLUDED
