#ifndef EN_TETE_H_INCLUDED
#define EN_TETE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

typedef struct
{
    int ID;
    char prenom[50];
    int score_partie;
    char jeton;
    int barriere;
}menu;

int run();

void gotoligcol( int lig, int col );
void Color(int couleurDuTexte,int couleurDeFond);
void efface();

void generation_plateau();
void info_partie(menu * infos);

void premier_tour(char tab[][2], int tour, int haut_bas,char jeton);
void traduction(char coord1, char coord2, int *coord_x, int *coord_y);

void traduction_barriere(char bari_x, char bari_y, char HV, int *barf_x, int *barf_y);

float menu_actions();
void menu_deplacement_pion(char tab[][2],int tour,char jeton,int ancien_tour,int coord_barrieres[][4],int compteur_barrieres);

void pose_barriere(int coord_barrieres[][4],int compteur_barrieres);

void score();
void afficher_aide();
float menu_du_jeu();

void fin_de_partie(char *gagnant);

#endif // EN_TETE_H_INCLUDED
