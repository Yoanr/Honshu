/**
 * \file play.c
 * \brief Ce fichier permet de démarrer et de jouer une partie complète de Honshu !
 */

#include "game.h"
#include "resolution.h"
#include "O_de_un.h"

int main(void)
{
    clear_term();
    
    int largeur = 50;
    int hauteur = 20;
    int largeurMenu = 22;
    int hauteurTuiles = 5;

    int nTuiles;

    Tuile* tuiles = tuiles_from_file("fichiers/tuiles", &nTuiles);
    Tuile* t2 = tuiles_from_file("fichiers/tuiles", &nTuiles);
    partie p = partie_from_file("fichiers/Partie1", tuiles, nTuiles);
    partie res = partie_from_file("fichiers/Partie1", t2, nTuiles);

    int score = game(largeur, hauteur, largeurMenu, hauteurTuiles, p);

    int bestscore = meilleur_score(res, 12);

    gotoxy(hauteur + 1, 0);
    printf(KWHT "Le jeu est fini. Score total : %d", score);
    gotoxy(hauteur + 1, 50);
    printf("Score maximal trouvé par le solveur : %d\n", bestscore);
    getchar();
    gotoxy(0, 0);
    clear_term();

    free_partie(p);
    free_partie(res);
    free_tableau(tuiles, nTuiles);
    free_tableau(t2, nTuiles);

	return 0;
}
