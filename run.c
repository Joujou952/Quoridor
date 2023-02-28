#include "en_tete.h"

int run()
{
    //d�but initialisation partie
    srand(time(NULL));
    char type_pion[8]= {'@','*','#','&','%','?','�','$'}; //tab des pions
    char coord_pions[4][2];
    int coord_barrieres[80][4];
    int compteur_barrieres = 0;
    char conditions_victoire[4];
    int i=0,nbr_joueur=0,choix_nbr_j=0,j=1;
    float choix_tour;
    int tour=0,ancien_tour=0,doublon=0,quite=0,compteur_tours=0;
    char haut_bas;
    menu* biblio;

    while(choix_nbr_j!=1)//tant que le choix est diff�rent de 1
    {
        printf("saisir le nombre de joueur:\n");//on demamde � l'utilisateur le nombres de joueuer
        scanf("%d",&nbr_joueur);
        fflush(stdin);//vider le buffer
        switch(nbr_joueur)
        {
        case 2://si c'est 2
            choix_nbr_j=1;//on ajoute 1
            break;//on sort de la boucle
        case 4://si c'est 4
            //pas fonctionnel pour l'instant
            return -1;
            break;//on sort
        }
    }
    biblio = (menu*)malloc(nbr_joueur*sizeof(menu));

    if(biblio==NULL)
    {
        printf("erreur de malloc\n");
        return 1;
    }


    do
    {
        i=rand()%8-1;//i prend une nouvelle valeur

        while(type_pion[i]=='X')//tant que la valeur du tab � l'emplacement i est NULL
        {
            i=rand()%8-1;//i prend une nouvelle valeur
        }
        biblio[j].ID = j;
        biblio[j].jeton = type_pion[i];//attribue le jeton au joueur correspondant
        printf("saisir le prenom du joueur[%d]\n",j);
        gets(biblio[j].prenom);//retour des noms des joueurs
        type_pion[i]='X';//la valeur du tableau � la case i est remplac� par rien
        j++;//on incr�mente notre compteur

    }
    while(j<=nbr_joueur); //la boucle tourne tant que le compteur est inf�reieur ou �gale au nombre de joueur

    for(int i=1; i<=nbr_joueur; i++) //pour i inf�ereieur au nombre de joueur
    {
        biblio[i].score_partie = 0;//initialisation du score � 0
        biblio[i].barriere = 20;//initialisation du nombre de barri�re � 20
    }
    //fin initialisation partie


    gotoligcol(0,0);
    generation_plateau();

    do
    {
        tour = rand()%2+1;      //la variable tour est utilis�e ici pour d�terminer le premier joueur a jouer et ensuite pour changer de joueur a chaque tour

        while(tour==doublon)//si c et le doublon ont la m�me valeur
        {
            tour = rand()%2+1;//c � une valeur al�atoire
        }
        info_partie(&biblio[tour]);//afficher les donner de la structure
        doublon = tour;// on lui ajoute la valeur de c
        //premier tour
        if(compteur_tours < 2)      //si les 2 joueurs n'ont pas plac� leur pion
        {
            if(compteur_tours < 1)          //pose des pions et d�finition de la condition de victoire
            {
                haut_bas = '1';
                conditions_victoire[tour-1] = '9';
            }
            else
            {
                haut_bas = '9';
                conditions_victoire[tour-1] = '1';
            }
            premier_tour(coord_pions, tour,haut_bas,biblio[tour].jeton);    //placer son pion
        }
        if(compteur_tours > 2)  //phase de jeu
        {
            choix_tour = menu_actions();    //affichage du menu des actions et demande d'un choix de l'action
            efface();                       //apr�s avoir re�u une entree on efface le menu des actions pour afficher le menu suivant
            switch((int)choix_tour)
            {
            case 1://si c'est 1
                menu_deplacement_pion(coord_pions,tour,biblio[tour].jeton,ancien_tour,coord_barrieres,compteur_barrieres);     //d�placer son pion
                if(conditions_victoire[tour-1] == coord_pions[tour-1][1])                                                      // si le pion est d�plac� sur la derni�re ligne le joueur a gagn�
                {
                    fin_de_partie(biblio[tour].prenom);          //affichage fin de partie
                    quite = 1;
                }
                break;
            case 2://si c'est 2                       //poser une barri�re
                if(biblio[tour].barriere > 0)           //si le joueur a assez de barri�res
                {
                    biblio[tour].barriere-=1;           //utilisation d'une barri�re
                    pose_barriere(coord_barrieres,compteur_barrieres);      //fonction de pose de barri�res
                    compteur_barrieres++;               //incr�mentation du nombre de barri�res pos�s
                }
                else
                {
                    printf("pas assez de barrieres");
                }
                break;
            case 3://si c'est 3
                //passage de tour                                //passer son tour
                break;
            case 4://si c'est 4                                                 //annuler la derni�re action
                //annuler derni�re action
                break;//on sort
            case 5://si c'est 5                                                 //retourner au menu principal
                quite = 1;
                break;//on sort
            }
        }
        ancien_tour = tour;
        tour=0;
        compteur_tours++;
        efface();

    }
    while(quite==0);
    return 0;
}
