#include "en_tete.h"
void traduction(char coord1, char coord2, int *coord_x, int *coord_y)       //traduction des coordonnées entrées en coordonnées de notre console (A1 => (4,2))
{
    *coord_x = (coord1 - 64) * 4;
    *coord_y = (coord2 - 48) * 2;
}

void traduction_barriere(char bari_x, char bari_y, char HV, int *barf_x, int *barf_y)        //i comme initail / f comme final
{
    int HVX = 0, HVY = 0;
    if(HV == 'G')
    {
        HVX = -2;
    }
    if(HV == 'D')
    {
        HVX = +2;
    }
    if(HV == 'H')
    {
        HVY = -1;
    }
    if(HV == 'B')
    {
        HVY = +1;
    }
    *barf_x = ((bari_x - 64) * 4) + HVX;
    *barf_y = ((bari_y - 48) * 2) + HVY;
}


void gotoligcol( int lig, int col )         //procédure de déplacement de curseur dans la console
{
// ressources
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


void generation_plateau()
{
    int Map[19][19]=
    {
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,-2},
        {-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
    };
    int ii,jj;
    int d = 1;
    printf("    A   B   C   D   E   F   G   H   I \n");

    for(ii=0; ii<19; ii++)
    {
        if((d)%2 == 0)
        {
            printf("%d",d/2);
        }
        else
        {
            printf(" ");
        }
        d=d+1;
        for(jj=0; jj<19; jj++)
        {
            switch(Map[ii][jj])
            {
            case(-2):
                printf("*");
                break;
            case(-1):
                printf(" *");
                break;
            case(0):
                printf("  ");
                break;
            case(1):
                printf(" |");
                break;
            case(2):
                printf("---");
                break;
            case(3):
                printf("+");
                break;
            }
        }
        printf(" \n");
    }
    printf(" \n");
}

void premier_tour(char tab[][2], int tour, int haut_bas,char jeton)  //procedure pour placer son pion sur le plateau
{
    char choix;             //déclaration des variables
    int mauvais_choix=0;
    int coord_x, coord_y;
    gotoligcol(20,0);       //affichage du texte en dessous du plateau
    printf("Entrez la colone dans laquelle vous voulez mettre votre pion (entre A et I):\n");
    do
    {
        if(mauvais_choix == 0)
        {
            printf("Saisie de l'action du joueur:\n");
        }
        if(mauvais_choix != 0)
        {
            gotoligcol(21,0);
            printf("vous n'avez pas entree une lettre comprise entre A et I essayer encore:\n              ");
            gotoligcol(22,0);
        }
        scanf("%c",&choix);
        fflush(stdin);
        mauvais_choix++;
    }while(choix != 'A' && choix != 'B' && choix != 'C' && choix != 'D' && choix != 'E' && choix != 'F' && choix != 'G' && choix != 'H' && choix != 'I');       //vérification de l'entrée et demande à nouveau celle-ci si pas comprise dans les 9 lettres de notre plateau
    tab[tour-1][0] = choix;         //stockage des coordonnées en x et y de notre pion dans coord_pions[][]
    tab[tour-1][1] = haut_bas;
    traduction(tab[tour-1][0], tab[tour-1][1], &coord_x, &coord_y);     //affichage du pion sur le plateau après avoir déplacé le curseur au bon endroit grâce aux procédures traduction et gotolicol
    gotoligcol(coord_y,coord_x);
    printf("%c",jeton);

}

void info_partie(menu * infos)      //affichage des informations de joueur sur la droite de l'écran
{
    gotoligcol(2,60);
    printf("id de joueurs:%d",infos->ID);
    gotoligcol(4,60);
    printf("Joueur:%s",infos->prenom);
    gotoligcol(6,60);
    printf("Score partie:%d",infos->score_partie);
    gotoligcol(8,60);
    printf("Jeton:%c",infos->jeton);
    gotoligcol(10,60);
    printf("Barrieres restantes:%d",infos->barriere);

}
