#include "resolution.h"

int resolution_recouv(partie p)
{
    GameState state = init_game_state(0, 0, 0, 0, p);

    int score;
    int i, j, r;
    int iMeilleur, jMeilleur, rMeilleur;
    int meilleurScore;
    int pose;

    while(trouver_indice_premiere_tuile(state) > -1)
    {
        state->tuileSelectionnee = trouver_premiere_tuile(state);
        state->indiceTuileSelectionnee = trouver_indice_premiere_tuile(state);
        iMeilleur = -1;
        jMeilleur = -1;
        rMeilleur = -1;
        meilleurScore = -1;
        pose = 0;

        /* On essaie de poser la tuile en ne recouvrant qu'une case */
        for (i = 0; i < state->g->dim; i++)
        {
            for (j = 0; j < state->g->dim; j++)
            {
                for (r = 0; r < 4; r++)
                {
                    if (nb_cases_recouvertes(i, j, state->tuileSelectionnee, state->g) == 1)
                    {
                        if (ajoute_tuile_safe(i, j, state->tuileSelectionnee, state->g))
                        {
                            score = calculer_score(state); 
                            pose = 1;
                            if (score > meilleurScore)
                            {
                                iMeilleur = i;
                                jMeilleur = j;
                                rMeilleur = r;
                                meilleurScore = score;
                            }
                            retire_derniere_tuile(state->g);
                        }
                    }
                }
            }
        }
        
        /* Si on n'a pas pu poser la tuile avec un seul recouvrement */
        if(!pose)
        {
            for (i = 0; i < state->g->dim; i++)
            {
                for (j = 0; j < state->g->dim; j++)
                {
                    for (r = 0; r < 4; r++)
                    {
                        if (ajoute_tuile_safe(i, j, state->tuileSelectionnee, state->g))
                        {
                            score = calculer_score(state); 
                            if (score > meilleurScore)
                            {
                                iMeilleur = i;
                                jMeilleur = j;
                                rMeilleur = r;
                                meilleurScore = score;
                            }
                            retire_derniere_tuile(state->g);
                        }
                    }
                }
            }            
        }

        /* On oriente et on pose la tuile comme on a trouvé que c'était bien */
        oriente(state->tuileSelectionnee, rMeilleur);
        if(ajoute_tuile_safe(iMeilleur, jMeilleur, state->tuileSelectionnee, state->g))
        {
            /* On retire la tuile des tuiles disponibles */
            int k;
            for (k = 0; k < state->tuilesDisponibles; k++)
            {
                if (state->tuiles[k] == state->tuileSelectionnee)
                {
                    state->tuiles[k] = NULL;
                    break;
                }
            }
        }

    }

    /* On affiche la grille et on retourne le score */
    affiche_grille_couleurs(state->g,5,50);
    score = calculer_score(state);
    free_grille(state->g); 
    free_state(state);
    return score;
}

int resolution(partie p) {
    GameState state = init_game_state(0, 0, 0, 0, p);

    int score;
    int i, j, r;
    int iMeilleur, jMeilleur, rMeilleur;
    int meilleurScore;

    while(trouver_indice_premiere_tuile(state) > -1) 
    {
        state->tuileSelectionnee = trouver_premiere_tuile(state);
        state->indiceTuileSelectionnee = trouver_indice_premiere_tuile(state);
        iMeilleur = 0;
        jMeilleur = 0;
        rMeilleur = 0;
        meilleurScore = 0;

        if (state->tuileSelectionnee == NULL)
            break;

        for (i = 0; i < state->g->dim; i++)
        {
            for (j = 0; j < state->g->dim; j++)
            {
                for (r = 0; r < 4; r++)
                {
                    if (ajoute_tuile_safe(i, j, state->tuileSelectionnee, state->g))
                    {
                        score = calculer_score(state); 
                        if (score > meilleurScore)
                        {
                            iMeilleur = i;
                            jMeilleur = j;
                            rMeilleur = r;
                            meilleurScore = score;
                        }
                        retire_derniere_tuile(state->g);
                    }
                }
            }
        }
        oriente(state->tuileSelectionnee, rMeilleur);
        ajoute_tuile_safe(iMeilleur, jMeilleur, state->tuileSelectionnee, state->g); 

        /* On retire la tuile des tuiles disponibles */
        int k;
        for (k = 0; k < state->tuilesDisponibles; k++)
        {
            if (state->tuiles[k] == state->tuileSelectionnee)
            {
                state->tuiles[k] = NULL;
                break;
            }
        }
    }

    affiche_grille_couleurs(state->g,5,50);
    /*gotoxy(1,70);
    printf("Score trouvé : %d\n", calculer_score(state));*/
    free_grille(state->g); 
    free_state(state);
    return meilleurScore;
}

void liberer_positions(Position* positions, GameState state)
{
    int i;
    for (i = 0; i < state->g->dim * state->g->dim; i++)
    {
        if (positions[i] == NULL)
            break;

        free(positions[i]);
    }

    free(positions);
}

Position* nouvelles_positions(GameState s) {
    int dimension = s->g->dim;
    int nbPossibilites = dimension * dimension * 4;
    Position* new_pos = malloc(nbPossibilites * sizeof(Position));
    Tuile t = s->tuileSelectionnee;

    int r, i, j;

    for (i = 0; i < nbPossibilites; i++)
        new_pos[i] = NULL;

    int indice = 0;
    for(r = 0; r < 4; r++){
        plus_pi_4(t);

        for(i = 0; i < dimension; i++)
        {
            for(j = 0;j < dimension; j++)
            {
                if(test_tout(t, i, j, s->g)) 
                {
                    Position p = malloc(sizeof(position));
                    p->x = i;
                    p->y = j;
                    p->rotation = t->orient;
                    new_pos[indice++] = p;
                }
            }
        }
    }
    return new_pos;
}
/*
int main(void)
{
    int nTuiles;
    Tuile* tuiles = tuiles_from_file("fichiers/tuiles", &nTuiles);
    partie p = partie_from_file("fichiers/Partie1", tuiles, nTuiles);

    int score_resol = resolution_recouv(p);

    printf("Score trouvé par la méthode d'Oxymore & Yoan: %d\n", score_resol);
    free_tableau(tuiles,nTuiles); 
    free_partie(p);
    return 0;
}*/
