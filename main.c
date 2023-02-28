#include "en_tete.h"

int main()
{
    float choix;                    //initialisation
    int quiter = 0 ;
    while(quiter == 0)              //tant qu'on ne sélectionne pas "quitter le jeu" le programme ne s'arrete pas
    {
        choix  = menu_du_jeu();     //affichage du menu du jeu
        switch((int)choix)
        {
        case 1://si c'est 1
            run();                  //lancement d'une nouvelle partie
            break;
        case 2://si c'est 2
            //charger_sauvegarde(); //chargement d'une partie sauvegardée
            break;
        case 3://si c'est 3
            afficher_aide();        //affichage des règles
            break;
        case 4:// si c'est 4
            score();                //affichage des scores
            break;
        case 5://si c'est 5
            quiter = 1;
            break;//on sort
        }
    }

    return 0;
}
