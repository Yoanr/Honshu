#include"O_de_un.h"


/**
 * \file implémentation d'une fonction de résolution du jeu de honshu.
 * \author Thibaut MILHAUD
 */

void recherche(GameState state, Grille G, int* S, int limit)
{
	/*compteurs*/

	int i;	/*tuiles*/
	int k;	/*position*/
	int r;	/*orientation*/

	int n = state->g->dim;

	if (state->g->nb_tuiles == 12)
	{
		/*mise à jour du village pour le calcul du score*/

		trouverVillageMax(state);

		/*mise à jour de G et S*/

		int temp = calculer_score(state);

		/* <==> cette solution est la meilleure rencontrée actuellement*/
		if (temp > *S)
		{	
			copie_grille(state->g, G);
			*S = temp;
		}
	}
	/*résolution gloutonne dans un premier temps*/
	else if (state->g->nb_tuiles < limit)
	{
		int s = 0;
		/*choix qui donne le meilleur score
		 * b = [i, k, r]
		 */
		int best[3];
		/*recherche de la valeur de best*/
		for (i = 1; i < 12; i++)
		{
			if (state->tuiles[i] != NULL)
			{		
				for (k = 0; k < n*n; k++)
				{
					for (r = 0; r < 4; r++)
					{
						oriente(state->tuiles[i], r);

						if (test_tout(state->tuiles[i], k/n, k%n, state->g))
						{
							/* mise à jour du game state
							 * ajout de la tuile */
							ajoute_tuile(k/n, k%n, state->tuiles[i], state->g);
							/* mettre la case i de tuiles à NULL*/
							
							int temp = calculer_score(state);

							if (temp > s)
							{
								s = temp;
								best[0] = i;
								best[1] = k;
								best[2] = r;
							}

							retire_derniere_tuile(state->g);
						}
					}
				}
			}
		}

		oriente(state->tuiles[best[0]], best[2]);

		ajoute_tuile(best[1]/n, best[1]%n, state->tuiles[best[0]], state->g);
		/*descente dans l'arborescense*/

		state->tuiles[best[0]] = NULL;
		
		recherche(state, G, S, limit);
	}

	/* exploration complete pout terminer */
	else
	{
		for (i = 1; i < 12; i++)
		{
			if (state->tuiles[i] != NULL)
			{		
				for (k = 0; k < n*n; k++)
				{
					for (r = 0; r < 4; r++)
					{	
						if (test_tout(state->tuiles[i], k/n, k%n, state->g))
						{
							/* mise à jour du game state
							 * ajout de la tuile */
							ajoute_tuile(k/n, k%n, state->tuiles[i], state->g);
							/* mettre la case i de tuiles à NULL*/
							state->tuiles[i] = NULL;
							/*appel récurssif*/

							recherche(state, G, S, limit);
							/* annulation des mises à jour */
							state->tuiles[i] = retire_derniere_tuile(state->g);
						}
						plus_pi_4(state->tuiles[i]);
					}
				}
			}
		}
	}
}

void copie_grille(Grille source, Grille cible)
{
	int i;
	int k;
	int k1;
	for (k=0; k<12; k++)
	{
		for (k1=0; k1<6; k1++)
		{
			cible->tuiles[k]->t->cases[k1] = source->tuiles[k]->t->cases[k1];
		}

		cible->tuiles[k]->t->orient = source->tuiles[k]->t->orient;
		cible->tuiles[k]->i = source->tuiles[k]->i;
		cible->tuiles[k]->j = source->tuiles[k]->j;
	}
	for (i=0; i < source->dim*source->dim; i++)
	{
		cible -> plateau[i] = source -> plateau[i];
	}
}

Grille grille_init(int n)
{
	Grille g = nouvelle_grille(n);
	int k;
	for (k=0; k<12; k++)
	{
		g->tuiles[k] = malloc(sizeof(tuile_posee));
		Tuile temp = rand_tuile();
		g->tuiles[k]->t = temp;
		g->tuiles[k]->i = 0;
		g->tuiles[k]->j = 0;
		g->nb_tuiles++;
	}
	return g;
}

int meilleur_score(partie p, int limit)
{
	/*initialisation*/
	int S;
	S = 0;
	GameState state = init_game_state(0, 0, 0, 0, p);
	Grille G = grille_init(state->g->dim);

	/*calcul*/
	recherche(state, G, &S, limit);

	/*affichage de la grille*/
	affiche_grille_couleurs(G, 5, 50);

	/*frees*/
	free_grille(G);
	free_grille(state->g);
	free_state(state);

	/*renvoie le meilleur score*/
	return S;
}
/*
int main(void)
{
	
    int nTuiles;

    Tuile* tuiles = tuiles_from_file("fichiers/tuiles", &nTuiles);
    partie p = partie_from_file("fichiers/Partie1", tuiles, nTuiles);

    GameState state = init_game_state(10, 10, 10, 10, p);

    meilleur_score(state, 12);

    free_state(state);
	free_partie(p);

    return 0;	
	int i;
	Tuile t = rand_tuile();
	for (i = 0; i<4; i++)
	{
		oriente(t, i);
		print_tuile(t);
	}
	Grille g = nouvelle_grille_avec_tuile(10);
	print_grille(g);
	plus_pi_4(t);
	ajoute_tuile(4, 5, t, g);
	print_grille(g);
	retire_derniere_tuile(g);
	print_grille(g);
	print_politique(g);
	retire_derniere_tuile(g);
	print_grille(g);
	return 0;
}
*/
