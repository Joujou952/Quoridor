#include "en_tete.h"

float menu_du_jeu()
{
    float choix;            //déclaration des variables
    int mauvais_choix=0;
    gotoligcol(0,0);        //effacer les anciennes informations sur la console
    printf("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      ");
    gotoligcol(0,0);
    printf("Menu:\n1- Lancer une nouvelle partie\n2- Reprendre une partie sauvegardee\n3- Afficher l aide\n4- Afficher les scores des joueurs\n5- Quitter le jeu\n");   //affichage du menu
    do
    {
        if(mauvais_choix == 0)
        {
            printf("Saisie de l'action du joueur:\n");
        }
        if(mauvais_choix != 0)      //si l'entrée n'est pas entre 1 et 5 on redemande une entrée avec le message suivant:
        {
            gotoligcol(6,0);
            printf("vous n'avez pas entree un entier compris entre 1 et 5 essayer encore:\n              ");
            gotoligcol(7,0);
        }
        scanf("%f",&choix);
        fflush(stdin);
        mauvais_choix++;
    }
    while(choix !=1.0 && choix !=2.0 && choix !=3.0 && choix !=4.0 && choix !=5.0);     //boucle do while permettant de blinder l'entrée du menu de jeu
    return choix;      //renvois de l'entrée
}

float menu_actions()  //menu des actions V1.1
{
    float choix;             //déclaration des variables
    int mauvais_choix=0;
    gotoligcol(20,0);       //placer le curseur en dessous du plateau
    printf("Actions possibles:\n1- deplacer son pion\n2- poser une barriere\n3- passer son tour\n4- annuler la derniere action\n5- quitter la partie\n");       //affichage du menu
    do
    {
        if(mauvais_choix == 0)
        {
            printf("Saisie de l'action du joueur:\n");
        }
        if(mauvais_choix != 0)      //si l'entrée n'est pas comprise entre 1 et 5 on redemande une entrée avec le message suivant:
        {
            gotoligcol(26,0);
            printf("vous n'avez pas entree un entier compris entre 1 et 5 essayer encore:\n              ");
            gotoligcol(27,0);
        }
        scanf("%f",&choix);
        fflush(stdin);
        mauvais_choix++;
    }
    while(choix !=1.0 && choix !=2.0 && choix !=3.0 && choix !=4.0 && choix !=5.0);     //boucle do while permettant de blinder l'entrée du menu des actions
    return choix;

}

void menu_deplacement_pion(char tab[][2],int tour,char jeton,int ancien_tour,int coord_barrieres[][4],int compteur_barrieres) // version 2
{
    int test,test2;                                        //déclaration des variables
    char coord_x_adv = tab[ancien_tour-1][0];       //coordonnées du pion adverse
    char coord_y_adv = tab[ancien_tour-1][1];
    char anciennes_coordx = tab[tour-1][0];         //stockage des anciennes coordonnées en x et y
    char anciennes_coordy = tab[tour-1][1];
    char coord_x,coord_y;                           //déclaration des coordonnées utilisées pour les inputs et pour les tests
    int lcoord_x,lcoord_y;                          //déclaration des coordonnées temporaires utilisées pour écrire dans la console
    int l2coord_x,l2coord_y;
    do
    {
        test2=0;
        do
        {
            gotoligcol(20,0);       //placer le curseur après le plateau
            test = 0;
            printf("Entrez une coordonnee en x \n");        //entrée des coordonnées en x et y
            scanf("%c",&coord_x);
            fflush(stdin);
            printf("Entrez une coordonnee en y \n");
            scanf("%c",&coord_y);
            fflush(stdin);
            efface();
            gotoligcol(24,0);

            if(coord_x > 'I' || coord_x < 'A') // Test si c'est dans le plateau en x
            {
                printf("Erreur dimension en horizontal ! Entrez de nouvelle coordonnee en x\n");
                test = 1;
            }
            if(coord_y > 58 || coord_y < 49 ) // Test si c'est dans le plateau en y
            {
                printf("Erreur dimension en vertical ! Entrez de nouvelle coordonnee en y \n");
                test = 1;
            }
            if(coord_x != (anciennes_coordx + 1) && coord_x  != (anciennes_coordx - 1) && coord_x  != (anciennes_coordx))  //test si déplacement de plus d'une case en x
            {
                printf("Erreur deplacement trop long en x\n");
                test = 1;
            }
            if(coord_y != (anciennes_coordy + 1) && coord_y  != (anciennes_coordy - 1) && coord_y  != (anciennes_coordy))  //test si déplacement de plus d'une case en x
            {
                printf("Erreur deplacement trop long en y\n");
                test = 1;
            }
            if(coord_x == anciennes_coordx && coord_y == anciennes_coordy)          //test si pion sur la même case
            {
                printf("Erreur pas de deplacement de pion\n");
                test = 1;
            }
            if(coord_x  != (anciennes_coordx) && coord_y  != (anciennes_coordy))       //test si déplacement en diagonale
            {
                printf("Erreur pas de deplacement en diagonale\n");
                test = 1;
            }
            if(coord_x == coord_x_adv && coord_y == coord_y_adv)                    //test si on se déplace sur un autre pion
            {
                printf("Erreur deplacement sur un pion adverse\n");
                test = 1; //fonction_saut_de_pion();
            }
        }
        while(test != 0);       //tant que tout les tests ne sont pas validés on demande de nouvelles entrées
        traduction(coord_x, coord_y, &lcoord_x, &lcoord_y);
        traduction(anciennes_coordx,anciennes_coordy,&l2coord_x,&l2coord_y);
        for(int i=0;i < compteur_barrieres;i++)                 //test de collisions avec toutes les barrières enregistrées
        {
            if(((lcoord_x+l2coord_x)/2 == coord_barrieres[i][0]) && ((lcoord_y+l2coord_y)/2 == coord_barrieres[i][1]))      //test collision avec première barrière du tableau
            {
                printf("barriere entre votre case actuelle et celle saisie\n");
                test2 = 1;
            }
            if(((lcoord_x+l2coord_x)/2 == coord_barrieres[i][2]) && ((lcoord_y+l2coord_y)/2 == coord_barrieres[i][3]))      //test collision avec deusième barrière du tableau
            {
                printf("barriere entre votre case actuelle et celle saisie\n");
                test2 = 1;
            }
        }
    }
    while(test2!=0);        //si aucune collision détectée
    traduction(coord_x, coord_y, &lcoord_x, &lcoord_y);     //on place le pion sur la nouvelle case après avoir déplacé le curseur sur la case voulue dans la console
    gotoligcol(lcoord_y, lcoord_x);
    printf("%c",jeton);
    traduction(anciennes_coordx,anciennes_coordy,&lcoord_x,&lcoord_y);  //on efface l'ancien emplacement de pion avec la même méthode
    gotoligcol(lcoord_y, lcoord_x);
    printf(" ");
    tab[tour-1][0] = coord_x;       //stockage des nouvelles coordonnées dans coord_pions[][]
    tab[tour-1][1] = coord_y;
}

void pose_barriere(int coord_barrieres[][4],int compteur_barrieres) // version 2
{
    //int plateau[40][4];
    char bar1_x,bar1_y,bar2_x,bar2_y;       //déclaration des variables
    int barf_x,barf_y;                      //coordonnées temporaires utilisées pour les traductions d'emplacement
    char HV;    //placement barrière Gauche ou droite ou haut ou bas    (horizontal ou vertical)
    int count1=0, count2=0, count3=0,count4=0;//compteur
    do
    {
        count4 = 0;
        do
        {
            count1 = 0;
            gotoligcol(20,0);//cuuseur en fin de ligne

            printf("entrer une valeur en ligne:\n");//coord en x
            scanf("%c",&bar1_x);
            fflush(stdin);

            printf("entrer une valeur en colonne:\n");//coord en y
            scanf("%c",&bar1_y);
            fflush(stdin);

            if(bar1_x > 'I' || bar1_x < 'A') // Test si c'est dans le plateau en x
            {
                printf("Erreur dimension en horizontal ! Entrez de nouvelle coordonnee en x\n");
                count1 = 1;
            }
            if(bar1_y > 58 || bar1_y < 49 ) // Test si c'est dans le plateau en y
            {
                printf("Erreur dimension en vertical ! Entrez de nouvelle coordonnee en y \n");
                count1 = 1;
            }

        }
        while(count1!=0);

        //coord bar1_x et bar1_y vérifiées
        efface();
        do
        {
            count2 = 0;
            gotoligcol(20,0);//cuuseur en fin de ligne

            printf("entrer une valeur en ligne:\n");//coord en x
            scanf("%c",&bar2_x);
            fflush(stdin);

            printf("entrer une valeur en colonne:\n");//coord en y
            scanf("%c",&bar2_y);
            fflush(stdin);
            if((bar2_x == bar1_x) && (bar2_y == bar1_y))    //test si superposition des 2 barrières
            {
                printf("Erreur superposition des barrieres impossible\n");
                count2 = 1;
            }
            if(bar2_x > 'I' || bar2_x < 'A') // Test si c'est dans le plateau en x
            {
                printf("Erreur dimension en horizontal ! Entrez de nouvelle coordonnee en x\n");
                count2 = 1;
            }
            if(bar2_y > 58 || bar2_y < 49 ) // Test si c'est dans le plateau en y
            {
                printf("Erreur dimension en vertical ! Entrez de nouvelle coordonnee en y \n");
                count2 = 1;
            }
            if(bar2_x != (bar1_x + 1) && bar2_x  != (bar1_x - 1) && bar2_x  != (bar1_x))  //test si déplacement de plus d'une case en x
            {
                printf("Erreur deplacement trop long en x\n");
                count2 = 1;
            }
            if(bar2_y != (bar1_y + 1) && bar2_y  != (bar1_y - 1) && bar2_y  != (bar1_y))  //test si déplacement de plus d'une case en x
            {
                printf("Erreur deplacement trop long en y\n");
                count2 = 1;
            }

        }
        while(count2!=0);

        //coord bar2_x et bar2_y vérifiées
        efface();
        do
        {
            count3 = 0;
            gotoligcol(20,0);//curseur en fin de ligne
            if(bar1_x == bar2_x)                            //si les 2 barrières sont dans la meme colone
            {
                printf("placez votre barriere a gauche ou a droite de ses coordonnées (G ou D):\n");//coord en x
                scanf("%c",&HV);
                fflush(stdin);
                if(HV != 'G' && HV != 'D')
                {
                    printf("Erreur de direction en x\n");   //si on entre pas G ou D
                    count3 = 1;
                }
                if(bar1_x == 'A' && HV == 'G')
                {
                    printf("Erreur exterieur du plateau en x\n");   //si en dehors du plateau (gauche de A)
                    count3 = 1;
                }
                if(bar1_x == 'I' && HV == 'D')
                {
                    printf("Erreur exterieur du plateau en x\n");   //si en dehors du plateau (droite de I)
                    count3 = 1;
                }
            }
            if(bar1_y == bar2_y)                        //si les 2 barrières sont dans la même ligne
            {
                printf("placez votre barriere en haut ou en bas de ses coordonnees (H ou B):\n");//coord en y
                scanf("%c",&HV);
                fflush(stdin);
                if(HV != 'H' && HV != 'B')
                {
                    printf("Erreur de direction en y\n");   //si on entre pas H ou B
                    count3 = 1;
                }
                if(bar1_y == '1' && HV == 'H')
                {
                    printf("Erreur exterieur du plateau en y\n");   //si en dehors du plateau (haut de 1)
                    count3 = 1;
                }
                if(bar1_y == '9' && HV == 'B')
                {
                    printf("Erreur exterieur du plateau en y\n");   //si en dehors du plateau (bas de 9)
                    count3 = 1;
                }
            }



        }
        while(count3!=0);
        efface();
        traduction_barriere(bar1_x, bar1_y, HV, &barf_x, &barf_y);      //si une barrière n'est pas placée au même endroit
        for(int i=0; i < compteur_barrieres; i++)
        {
            if(coord_barrieres[i][0] == barf_x && coord_barrieres[i][1] == barf_y)
            {
                printf("barriere deja existante\n");
                count4=1;
            }
            if(coord_barrieres[i][2] == barf_x && coord_barrieres[i][3] == barf_y)
            {
                printf("barriere deja existante\n");
                count4=1;
            }
        }
        traduction_barriere(bar2_x, bar2_y, HV, &barf_x, &barf_y);      //si une barrière n'est pas placée au même endroit
        for(int i=0; i < compteur_barrieres; i++)
        {
            if(coord_barrieres[i][0] == barf_x && coord_barrieres[i][1] == barf_y)
            {
                printf("barriere deja existante\n");
                count4=1;
            }
            if(coord_barrieres[i][2] == barf_x && coord_barrieres[i][3] == barf_y)
            {
                printf("barriere deja existante\n");
                count4=1;
            }
        }

    }
    while(count4 != 0);
    //barrières vérifiées

    traduction_barriere(bar1_x, bar1_y, HV, &barf_x, &barf_y);      //affichage barrière 1 sur le plateau
    gotoligcol(barf_y, barf_x);
    printf("B");

    coord_barrieres[compteur_barrieres][0] = barf_x;                //stockage de ses coordonnées dans coord_barrieres
    coord_barrieres[compteur_barrieres][1] = barf_y;

    traduction_barriere(bar2_x, bar2_y, HV, &barf_x, &barf_y);      //affichage barrière 2 sur le plateau
    gotoligcol(barf_y, barf_x);
    printf("B");

    coord_barrieres[compteur_barrieres][2] = barf_x;                //stockage de ses coordonnées dans coord_barrieres
    coord_barrieres[compteur_barrieres][3] = barf_y;
}


void afficher_aide()
{
    int Quit;

    gotoligcol(0,0);        //effacer le texte précedant
    printf("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ");
    gotoligcol(0,0);        //affichage des règles
    printf("VOICI LES REGLES DU JEU : \n\nIl s'agit d'atteindre le premier la ligne opposee a sa ligne de depart.\n\nEn debut de partie, les barrieres sont remisees dans leur zone de stockage. Chaque joueur pose son pion au centre de sa ligne de depart (la premiere ligne face a lui).\nUn tirage au sort determine qui commence.\n\nDEPLACEMENTS\nA tour de role, chaque joueur choisit :\n -de deplacer son pion d'une case verticalement ou horizontalement, en avant ou en arriere; \n -de poser une de ses barrieres. Une barriere doit etre posee exactement entre deux blocs de 2 cases. \nLorsqu'il n'a plus de barrieres, un joueur est oblige de deplacer son pion.\nLa pose des barrieres a pour but de se creer son propre chemin ou de ralentir d'adversaire, mais il est interdit de lui fermer totalement l'acces a sa ligne de but.\n\nQuand 2 pions se retrouvent en vis-a-vis sur 2 cases voisines non separees par une barriere, \nle joueur dont c'est le tour peut sauter par-dessus son adversaire et se retrouver derriere lui. \nSi une barriere se trouve derriere le pion saute, le joueur peut choisir de bifurquer a droite ou a gauche du pion saute\n\nPour revenir au menu principale tapez 1\n");
    gotoligcol(22,0);
    do
    {
        scanf("%d",&Quit);
        fflush(stdin);
        if(Quit != 1)
        {
            gotoligcol(21,0);
            printf("                                                                        ");
            gotoligcol(21,0);
            printf("Vous devez entre 1\n");
            gotoligcol(22,0);
        }
    }
    while(Quit != 1);   // si on entre 1 on retourne au menu précedant
}

void score()
{
    int Quit;

    gotoligcol(0,0);        //effacer le texte précedant
    printf("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ");
    gotoligcol(0,0);        //affichage des scores
    printf("VOICI LES SCORES DU JEU : \n\nPour revenir au menu principale tapez 1\n"); // Print du tableau a beber des scores
    gotoligcol(3,0);
    do
    {
        scanf("%d",&Quit);
        fflush(stdin);
        if(Quit != 1)
        {
            gotoligcol(2,0);
            printf("                                                                        ");
            gotoligcol(2,0);
            printf("Vous devez entre 1\n");
            gotoligcol(3,0);
        }
    }
    while(Quit != 1);   // si on entre 1 on retourne au menu précedant
}


void fin_de_partie(char *gagnant)
{
    int Quit;

    gotoligcol(0,0);        //effacer le texte précedant
    for(int i=0; i<3; i++)
    {
        printf("                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ");
    }
    gotoligcol(0,0);        //affichage des règles
    printf("Le joueur %s a gagne \n appuyez sur 1 pour quitter",gagnant);
    gotoligcol(2,0);
    do
    {
        scanf("%d",&Quit);
        fflush(stdin);
        if(Quit != 1)
        {
            gotoligcol(21,0);
            printf("                                                                        ");
            gotoligcol(21,0);
            printf("Vous devez entre 1\n");
            gotoligcol(22,0);
        }
    }
    while(Quit != 1);   // si on entre 1 on retourne au menu précedant
}

void efface()       //procédure permetant de suprimmer le texte précédant dans la console (en dessous du plateau)
{
    gotoligcol(20,0);
    printf("                                                                                                                                ");
    printf("                                                                                                                                ");
    printf("                                                                                                                                ");
    printf("                                                                                                                                ");
    printf("                                                                                                                                ");
    printf("                                                                                                                                ");
    printf("                                                                                                                                ");
}


