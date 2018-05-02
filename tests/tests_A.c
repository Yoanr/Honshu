/**
 * \file tests_A.c
 * Fichier qui contient la fontion main : pour l'instant elle sert surtout à voir comment le script s'exécute et à tester les fonctions.
 */ 


#include"../librairies/tuile.h"
#include"../librairies/grille.h"
#include"../librairies/test.h"

int main()
{
	int n = 10;
	
	Grille g = nouvelle_grille_avec_tuile(n);

	/* je met en commentaire pour tester retire tuile
	 *
	 *
	int nTuiles;
	Tuile* tuiles = tuiles_from_file("fichiers/tuiles_oxy", &nTuiles);

	int i;

	for (i = 0; i < nTuiles; i++)
	{
		print_tuile(tuiles[i]);
		printf("\n");
	}
	
	for (i = 0; i < 3; i++)
		ajoute_tuile(3 * i, 2 * i, tuiles[i], g);


	TESTS DE LA FONCTION VILLAGE_ASSOCIE
	for (i = 0; i < nTuiles; i++) {
		ajoute_tuile_safe(0, 0, tuiles[i], g);		
	}

	print_grille(g);
	print_politique(g);

	int* village = malloc(sizeof(g->dim * g->dim));
	int nVillage = village_associe(village, 2, 1, g);
	printf("%p de taille %d\n", village, nVillage);

	free(village);
	free_tableau(tuiles, nTuiles);
	*
	*
	*/

	Tuile t = rand_tuile();

	ajoute_tuile(3,4,t,g);

	print_politique(g);

	int k;
	for(k=0;k<3;k++)
	{
		free(retire_derniere_tuile(g));
		print_politique(g);
	}


	free_grille(g);
	
	return 0;

	
}
