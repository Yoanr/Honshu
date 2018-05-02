/**
 * \file O_de_un.h 
 * \brief interface d'une fonction de résolution du jeu de honshu.
 * \author Thibaut MILHAUD
*/

#include<time.h>
#include"tuile.h"
#include"grille.h"
#include"test.h"
#include"game.h"

/**
 * \author Thibaut MILHAUD
 * \brief Fonction récursive qui va explorer toute les possibilités d'une partie et renvoyer la meilleure.
 * \param state un Gamestate
 * \param G la grille qui contient la meilleure solution rencontrée à ce moment ce de l'exploration.
 * \param S le score de G.
 * \param limit indique combien de tuile doivent être posées avant de faire une exploration totale
 * \warning Pour le premier appel de la fonction, il faut que la \b G ne contienne que la tuile de départ et que \b S soit négatif.
 */

void recherche(GameState state, Grille G, int* S, int limit);


/**
 * \author Thibaut MILHAUD
 * \brief Fonction de copie par valeur d'une \b Grille.
 * \param source la \b Grille à copier.
 * \param cible la \b Grille dans laquelle il faut copie
 * \warning Les tuiles ne sont effectivement poées dans la grille qu'une fois que l'exploration est terminée, en attendant on ne récupère que les postions, orientation et les cases des tuiles.
 */

void copie_grille(Grille source, Grille cible);

/**
 * \author Thibaut MILHAUD
 * \brief Initialise une grille avec 12 tuiles posées en (0,0). Cette fonction permet d'initialiser les case mémoires pour stocker notre solution actuelle.
 * \param n la taille de la grille demandée
 * \warning Les tuiles ne sont effectivement poées dans la grille qu'une fois que l'exploration est terminée, en attendant on ne récupère que les postions, orientation et les cases des tuiles.
 */

Grille grille_init(int n);

/**
 * \author Thibaut MILHAUD
 * \brief renvoie un bon score étant donné une situation initiale.
 * \param limit un entier qui spécifie combien de tuiles on doit poser avant de passer en mode exploration totale
 * \param p une \b partie 
 * \return LE meilleur score (si limit = 0), un bon score sinon
 */

int meilleur_score(partie p, int limit);
