#ifndef GAME_H
#define GAME_H

/**
 * \file game.h
 * \brief ce fichier contient le squelette des fonctions qui vont être implémentées et utilisées dans game.c pour l'affichage du jeu dans le terminal
 */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "test.h"

/**
 * Les différentes couleurs utilisables dans le terminal
 */
#define KHIG  "\033[1m"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

/**
 * \def max(x, y)
 * \brief Renvoie le max entre deux nombres
 */
#define max(x, y) (((x) > (y)) ? (x) : (y))

/**
 * \def min(x, y)
 * \brief Renvoie le min entre deux nombres
 */
#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 * \def clear_term()
 * \brief Efface le terminal
 */
#define clear_term() printf("\033[H\033[J")

/**
 * \def gotoxy(x, y)
 * \brief Déplace le curseur sur le terminal en (\b x, \b y)
 */
#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))

/**
 * \author Thomas Kowalski
 * \struct gameState
 * \brief Représente un état de jeu (que l'on peut alors représenter graphiquement)
 */
struct gameState {
    Grille g; /*!< La grille de jeu */
    Tuile* tuiles; /*!< Les tuiles disponibles pour être posées par le joueur. */

    int tuilesDisponibles; /*!< La taille de \b tuiles */

    int iNouvelleTuile; /*!< La ligne où le joueur aimerait poser sa tuile. */
    int jNouvelleTuile; /*!< La colonne où le joueur aimerait poser sa tuile. */

    Tuile tuileSelectionnee; /*!< La tuile sélectionnée par le joueur. */
    int indiceTuileSelectionnee; /*!< L'indice dans la main du joueur de la tuile sélectionnée */

    int largeur; /*!< La largeur du terminal */
    int hauteur; /*!< La hauteur du terminal */
    int largeurMenu; /*!< La largeur du menu de gauche */
    int hauteurTuiles; /*!< La hauteur de la liste de tuiles */
    int tailleVillageMax; /*!< La taille du plus grand village de la grille */
    int* villageMax; /*!< Le plus grand village de la grille*/
    int score; /*!< Le score actuel de la grille */
};

/**
 * \typedef Raccourci pour \b struct \b gameState
 */
typedef struct gameState gameState;

/**
 * \typedef un pointeur vers un \b gameState
 */
typedef gameState* GameState;

/**
 * \author Thomas Kowalski
 * \enum touche
 * \brief Représente différentes valeurs de touches appuyées par l'utilisateur
 */
enum touche
{
    Haut = 65,       /*!< La touche directionnelle \b Haut */
    Droite = 67,     /*!< La touche directionnelle \b Droite */
    Bas = 66,        /*!< La touche directionnelle \b Bas */
    Gauche = 68,     /*!< La touche directionnelle \b Gauche */
    Rotation = 114,  /*!< La touche \b r */
    Placement = 112, /*!< La touche \b p */
    Precedent = 97,  /*!< La touche \b a */
    Suivant = 122    /*!< La touche \b z */
};

/**
 * \author Thomas Kowalski
 * \brief Lance le jeu.
 * \return 0 si tout se passe bien, 1 en cas d'erreur grave.
 */
int main();

/**
 * \author Thomas Kowalski
 * \brief Boucle principale du jeu : gère les entrées clavier et les opérations sur la partie.
 * \return Le score remporté par le joueur.
 */
int game();

/**
 * \author Thomas Kowalski
 * \brief Détermine le plus grand village dans la grille d'un état
 * \param state l'état dont on veut calculer le plus grand village
 */
void trouverVillageMax(GameState state);

/**
 * \author Thomas Kowalski
 * \brief Libère tout l'espace alloué pour un état
 * \param state l'état
 */
void liberer_state(GameState state);

/**
 * \author Matthis Pillonel
 * \brief Calcule le score actuel de la partie 
 * \param state l'état actuel du jeu
 * \return Le score de la grille.
 */
int calculer_score(GameState state);

int calcul_Lac(int* Lacs, int i, int j, Grille g);

/**
 * \author Thomas Kowalski
 * \brief Trouve le plus grand village associé à une case dans une grille
 * \param Village un pointeur vers un tableau d'entiers (à remplir)
 * \param i la ligne de la case
 * \param j la colonne de la case
 * \param g la grille
 * \return la taille du village max
 */
int calcul_Village(int* Village, int i, int j, Grille g);

/**
 * \author Thibaut Milhaud
 * \brief Affiche le score actuel de la grille
 * \param state l'état du jeu
 * \param x la ligne où afficher le score
 * \param y la colonne où afficher le score
 */
void print_score(GameState state, int x, int y);

/**
 * \brief Met à jour toutes les parties de l'affichage.
 * \param state l'état du jeu
 */
void update(GameState state);

/**
 * \brief Met à jour l'affichage de la grille.
 * \param state l'état du jeu
 */
void updateGrille(GameState state);

/**
 * \author Thomas Kowalski
 * \brief Affiche les tuiles disponibles
 * \param state l'état du jeu
 */
void updateTuileAPlacer(GameState state);

/**
 * \author Thibaut Milhaud
 * \brief Affiche la tuile en cours de pose
 * \param state l'état actuel du jeu
 */
void updateTuileEnCours(GameState state);

/**
 * \author Thomas Kowalski
 * \brief Trouve la première tuile non encore posée (ie non \b NULL) dans les \b tuiles d'un état.
 * \param state l'état du jeu
 * \return un pointeur vers la première tuile disponible, \b NULL si toutes les tuiles ont été posées.
 */
Tuile trouver_premiere_tuile(GameState state);

/**
 * \author Yoan Rock
 * \brief Trouve l'indice de la première tuile non encore posée (ie non \b NULL) dans les \b tuiles d'un état.
 * \param state l'état du jeu
 * \return l'indice vers la première tuile disponible, \b -1 si toutes les tuiles ont été posées.
 */
int trouver_indice_premiere_tuile(GameState state);

/**
 * \author Thomas Kowalski
 * \brief Initialise l'état du jeu (début de la partie)
 * \param largeur la largeur du terminal
 * \param hauteur la hauteur du terminal
 * \param largeurMenu la largeur que devrait prendre la colonne du menu
 * \param hauteurTuiles la hauteur de la ligne contenant les tuiles disponibles
 * \param p la partie (chargée depuis un fichier) sur laquelle lancer le jeu.
 * \return L'état initialisé.
 */
GameState init_game_state(int largeur, int hauteur, int largeurMenu, int hauteurTuiles, partie p);

/**
 * \brief Fonction d'affichage de la grille de la tuile que l'on est en train de poser en couleur
 * \author Thibaut Milhaud
 * \param t la Tuile que l'on est en train de positionner
 * \param g la grille de jeu
 * \param x abscisse du coin haut gauche de la tuile
 * \param y ordonnée de ce même coin
 * \param i abscisse du coin haut gauche la tuile dans la grille
 * \param j ordonnée du coin haut gauche la tuile dans la grille
 * \warning si i>n-1 ou j>n-1 on ne verra jamais la tuile à l'écran
 * \warning si la tuile dépasse de la grille je sais pas trop comment faire
 */
void affiche_plateau_2_jeu(Tuile t, Grille g, int x, int y, int i, int j);

/**
 * \brief Fonction d'affichage d'une grille en couleurs au bon endroit
 * \author Thibaut MILHAUD
 * \param g la \b Grille à afficher
 * \param x abscisse du coin haut gauche de la tuile
 * \param y ordonnée de ce même coin
 */
void affiche_grille_couleurs(Grille g, int x, int y);

/**
 * \brief Affiche (en bas de l'écran) les tuiles posables par le joueur
 * \author Thibaut Milhaud
 * \param hauteur la hauteur de la liste des tuiles disponibles
 * \param tuiles la main du joueur
 * \param indiceTuileSelectionnee la tuile en train d'être posée
 */
void affiche_tuile_dispo(int hauteur, Tuile* tuiles, int indiceTuileSelectionnee);

/**
 * \author Thomas Kowalski
 * \brief Dessine le cadre de l'affichage (séparation menu, grille, tuiles)
 * \param largeur la largeur du terminal
 * \param hauteur la hauteur du terminal
 * \param largeurMenu la largeur du menu de gauche
 * \param hauteurTuiles la hauteur de la prévisualisation des tuiles
 */
void dessiner_cadre(int largeur, int hauteur, int largeurMenu, int hauteurTuiles);

/**
 * \author Thomas Kowalski
 * \brief Libère l'espace mémoire utilisé par un GameState
 * \param state le GameState à libérer
 */
void free_state(GameState state); 

#endif
