#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "test.h"
#include "game.h"
#include "tuile.h"

struct position{
    int x;/*!<Coordonnée x du coin supérieur gauche*/
    int y;/*!<Coordonnée y du coin supérieur gauche*/
    card rotation;/*!<Orientation de la tuile*/
};

typedef struct position position;

typedef struct position* Position;

/**
 * \author Matthis Pillonel
 * \brief Effectue une résolution par essaies successifs.
 * \param p une Partie
 * \return le score maximal obtenue
 */
int resolution(partie p);

int resolution_recouv(partie p);

/**
 * \author Matthis Pillonel
 * \brief Permet de connaitre l'orientation après une rotation de 90°
 * \param t une Tuile
 * \return card correspondant à l'orientaion après une rotation de 90°
 
card nextOrient(Tuile t);
*/


/**
 * \author Matthis Pillonel
 * \brief Remplie une liste de position contenant l'ensemble des positions accessibles depuis le GameState
 * \param s un GameState
 * \return une Position* contenant l'ensemble des nouveaux états accessibles par s
 **/
Position* nouvelles_positions(GameState s);

/**
 * \author Thomas Kowalski
 * \brief Libère la liste de positions créée par nouvelle_positions
 * \param positions le tableau de positions à libérer
 * \param state l'état du jeu (pour avoir le côté de la grille)
 */
void liberer_positions(Position* positions, GameState state);

#endif