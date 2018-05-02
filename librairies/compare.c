
/**
 * \file compare.c
 * \brief Ce fichier permet de comparer les solveurs
 */

#include "game.h"
#include "resolution.h"
#include "O_de_un.h"

int main(void)
{
    clear_term();
    int nTuiles;

    /* pour comprarer les trois solveurs */
    
    Tuile* t1 = tuiles_from_file("fichiers/tuiles", &nTuiles);
    Tuile* t2 = tuiles_from_file("fichiers/tuiles", &nTuiles);
    Tuile* t3 = tuiles_from_file("fichiers/tuiles", &nTuiles);
    partie p1 = partie_from_file("fichiers/Partie1", t1, nTuiles);
    partie p2= partie_from_file("fichiers/Partie1", t2, nTuiles);
    partie p3 = partie_from_file("fichiers/Partie1", t3, nTuiles);

    int s1 = resolution(p1);
    int s2 = resolution_recouv(p2);
    int s3 = meilleur_score(p3, 12);

    clear_term();

    printf(KWHT "algorithme glouton sans changer l'ordre : %i\n algorithme expensif : %i\n algorithme glouton qui change l'ordre : %i\n", s1, s2, s3);  

    free_partie(p1);
    free_partie(p2);
    free_partie(p3);
    free_tableau(t1, nTuiles);
    free_tableau(t2, nTuiles);
    free_tableau(t3, nTuiles);

	return 0;
}
