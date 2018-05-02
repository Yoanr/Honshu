/**
 * \file main.c
 * Fichier qui contient la fontion main : pour l'instant elle sert surtout à voir comment le script s'exécute et à tester les fonctions.
 */ 


#include"../librairies/tuile.h"
#include"../librairies/grille.h"
#include"../librairies/test.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#define n 10

void tests_charger_Grille()
{
	partie p;

	int nTuiles;
	Tuile* tuiles = tuiles_from_file("fichiers/tuiles", &nTuiles);

	/* Chargement d'une grille dans un mauvais format */
	p = partie_from_file("fichiers/grille_mauvais_format", tuiles, nTuiles);
	CU_ASSERT_PTR_NULL(p.identifiantsTuiles);
	CU_ASSERT_PTR_NULL(p.mainJoueur);

	/* Chargement d'une grille déclarant plus de tuiles qu'elle n'en donne */
	p = partie_from_file("fichiers/grille_pas_assez_tuiles", tuiles, nTuiles);
	CU_ASSERT_PTR_NULL(p.identifiantsTuiles);
	CU_ASSERT_PTR_NULL(p.mainJoueur);

	/* Chargement d'une grille demandant une tuile de départ inexistante */
	p = partie_from_file("fichiers/grille_mauvais_identifiant_tuile", tuiles, nTuiles);
	CU_ASSERT_PTR_NULL(p.identifiantsTuiles);
	CU_ASSERT_PTR_NULL(p.mainJoueur);

	/* Chargement d'une grille correcte */
	p = partie_from_file("fichiers/Partie1", tuiles, nTuiles);
	CU_ASSERT_PTR_NOT_NULL(p.identifiantsTuiles);
	CU_ASSERT_PTR_NOT_NULL(p.mainJoueur);

	/* Vérification que les identifiants de tuiles sont bien chargés */
	CU_ASSERT_EQUAL(p.identifiantsTuiles[0], 13);
	CU_ASSERT_EQUAL(p.identifiantsTuiles[p.nbTuiles - 1], 3);

	/* Vérification de la taille de la grille */
	CU_ASSERT_EQUAL(p.tailleGrille, 9);

	/* Vérification que la tuile posée au départ est bien correcte */
	CU_ASSERT_EQUAL(p.idTuileDepart, 13);

	/* Vérification que la main est dans le bon ordre */
	CU_ASSERT_EQUAL(p.mainJoueur[0]->identifiant, 13);
	CU_ASSERT_EQUAL(p.mainJoueur[1]->identifiant, 7);
	CU_ASSERT_EQUAL(p.mainJoueur[2]->identifiant, 2);
	CU_ASSERT_EQUAL(p.mainJoueur[p.nbTuiles - 1]->identifiant, 3);

	/* Libération des ressources allouées */
	free_partie(p);

	/* Libération des ressources allouées pour le chargement des tuiles */
	free_tableau(tuiles, nTuiles);
}

void tests_charger_Tuiles()
{
	int nTuiles;
	Tuile* tuiles;
	
	/* Chargement d'un fichier avec un terrain invalide */
	tuiles = tuiles_from_file("fichiers/tuiles_mauvais_terrain", &nTuiles);
	CU_ASSERT_PTR_NULL(tuiles);
	CU_ASSERT_EQUAL(nTuiles, -1);

	/* Chargement d'un fichier avec des tuiles manquantes par rapport à ce qui est indiqué */
	tuiles = tuiles_from_file("fichiers/tuiles_pas_assez_tuiles", &nTuiles);
	CU_ASSERT_PTR_NULL(tuiles);
	CU_ASSERT_EQUAL(nTuiles, -1);

	/* Chargement d'un fichier correct (21 tuiles) */
	tuiles = tuiles_from_file("fichiers/tuiles", &nTuiles);
	CU_ASSERT_PTR_NOT_NULL(tuiles);
	CU_ASSERT_EQUAL(nTuiles, 21);
	
	/* Nettoyage */
	free_tableau(tuiles, nTuiles);
}

void tests_Grille()
{
	Grille g = nouvelle_grille_avec_tuile(n);
	CU_ASSERT_PTR_NOT_NULL(g);

	int nTuiles;
	Tuile* tuiles = tuiles_from_file("fichiers/tuiles_oxy", &nTuiles);
	CU_ASSERT_PTR_NOT_NULL(tuiles);

	ajoute_tuile_safe(6, 5, tuiles[0], g);

	/* Détermination d'un village existant */
	int* village = malloc(sizeof(int) * g->dim * g->dim);
	int nVillage = village_associe(village, 8, 5, g);

	CU_ASSERT_NOT_EQUAL(village[0], -1);
	CU_ASSERT_NOT_EQUAL(nVillage, 0);

	/* Détermination d'un village à partir d'une case non-village */
	nVillage = village_associe(village, 4, 1, g);

	CU_ASSERT_EQUAL(village[0], -1);
	CU_ASSERT_EQUAL(nVillage, 0);
	
	free(village);
	free_grille(g);
	free_tableau(tuiles, nTuiles);
}

void tests_Tuile()
{
	/* Génération tuile aléatoire */
	Tuile t = rand_tuile();
	CU_ASSERT_PTR_NOT_NULL(t);

	/* Génération d'une grille avec une tuile aléatoire */
	Grille g = nouvelle_grille_avec_tuile(n);

	free(t);
	free_grille(g);
}

void tests_recouvrement_Tuiles()
{
	Grille g = nouvelle_grille_avec_tuile(10);

	Tuile t1 = rand_tuile();
	oriente(t1,O_N);
	CU_ASSERT_EQUAL(verifier_non_couvrement_total(t1,0,0,g),1);
	ajoute_tuile(0,0,t1,g);
	Tuile t2 = rand_tuile();
	oriente(t2,O_N);
	CU_ASSERT_EQUAL(verifier_non_couvrement_total(t2,0,0,g),0);
	CU_ASSERT_EQUAL(verifier_non_couvrement_total(t2,0,2,g),1);

	ajoute_tuile(0,2,t2,g);

	Tuile t3 = rand_tuile();
	oriente(t3,O_N);

	CU_ASSERT_EQUAL(verifier_non_couvrement_total(t3,0,1,g),1);
	ajoute_tuile(0, 4, t3, g);

	free_grille(g);

}

void tests_dont_fill_lake()
{
	Grille g = nouvelle_grille_avec_tuile(10);
	Tuile t1 = rand_tuile();
	int i;
	char cases[6] = {'P', 'F', 'L', 'V', 'R', 'U'};
	for (i = 0; i < 6; i++)
		t1->cases[i] = (kase)cases[2];

	t1->orient = 0;
	oriente(t1, O_N);

	ajoute_tuile(0, 0, t1,g);

	Tuile t2 = rand_tuile();
	for (i = 0; i < 6; i++)
		t2->cases[i] = (kase)cases[2];

	t2->orient = 0;
	oriente(t1, O_N);

	int result = dont_fill_lake(t2, 0, 1, g);
	CU_ASSERT_EQUAL(result, 0);
	ajoute_tuile(4, 0, t2, g);

	free_grille(g);
}

void tests_is_in_grid() 
{

	Grille g = nouvelle_grille(10);
	Tuile t1 = rand_tuile();
	oriente(t1,O_N);
	
	CU_ASSERT_EQUAL(is_ingrid(t1,9,9,g),0);
	CU_ASSERT_EQUAL(is_ingrid(t1,8,8,g),0);
	CU_ASSERT_EQUAL(is_ingrid(t1,0,0,g),1);
	CU_ASSERT_EQUAL(is_ingrid(t1,6,6,g),1);
	
	free(t1);
	free_grille(g);
}
void tests_is_connected(){
	Grille g = nouvelle_grille_avec_tuile(10);

	/* Tuile aléatoire qu'on va tenter de placer */
	Tuile t1 = rand_tuile();
	oriente(t1, O_N);

	/* Vérification qu'on est connecté en ajoutant à gauche */
	CU_ASSERT_EQUAL(is_connected(t1, 3, 3, g), 1);
	/* Au dessus */
	CU_ASSERT_EQUAL(is_connected(t1, 3, 4, g), 1);
	/* Directement sur la tuile */
	CU_ASSERT_EQUAL(is_connected(t1, 5, 4, g), 1);
	CU_ASSERT_EQUAL(is_connected(t1, 4, 5, g), 1);

	/* Vérification qu'on n'est pas connecté */
	CU_ASSERT_EQUAL(is_connected(t1, 7, 6, g), 0);
	CU_ASSERT_EQUAL(is_connected(t1, 8, 6, g), 0);

	/* Libération de la mémoire allouée pour les tests */
	free(t1);
	free_grille(g);
}

void tests_cases_recouvertes()
{
	/* Définition d'une grille de départ aléatoire */
	Grille g = nouvelle_grille_avec_tuile(10);

	Tuile t1 = rand_tuile();
	oriente(t1, O_N);

	/* Test de recouvrement avec tuile en dehors */
	int* recouvert = cases_recouvertes(8, 8, t1, g);
	CU_ASSERT_PTR_NULL(recouvert);

	/* Récupération des cases recouvertes dans une situation normale */
	recouvert = cases_recouvertes(4, 4, t1, g);
	CU_ASSERT_PTR_NOT_NULL(recouvert);
	
	/* Comparaison avec les valeurs obtenues en posant effectivement la tuile */
	CU_ASSERT_EQUAL(recouvert[0], 44);
	CU_ASSERT_EQUAL(recouvert[1], 45);
	CU_ASSERT_EQUAL(recouvert[2], 54);
	CU_ASSERT_EQUAL(recouvert[3], 55);
	CU_ASSERT_EQUAL(recouvert[4], -1);
	CU_ASSERT_EQUAL(recouvert[5], -1);

	/* Libération des ressources */
	free(recouvert);
	free(t1);
	free_grille(g);
}

void tests_ajout_tuile_safe()
{
	/* Définition d'une grille de départ aléatoire */
	Grille g = nouvelle_grille(10);
	
	/* Tuile aléatoire que l'on va poser au début */
	Tuile tDebut = rand_tuile();
	oriente(tDebut, O_E);
	/* Suppression des lacs (on veut être sûr de pouvoir poser la tuile pour ce test) */
	int i;
	for (i = 0; i < 6; i++)
		if (tDebut->cases[i] == L)
			tDebut->cases[i] = P;

	ajoute_tuile(g->dim / 2 - 1, g->dim / 2 - 1, tDebut, g);

	Tuile t1 = rand_tuile();
	oriente(t1, O_N);
	
	CU_ASSERT_EQUAL(ajoute_tuile_safe(4, 4, t1, g), 1);
	
	Tuile t2 = rand_tuile();
	oriente(t2, O_N);
	CU_ASSERT_EQUAL(ajoute_tuile_safe(8, 6, t2, g), 0);

	/* On doit free t2 puisqu'on ne l'a pas ajoutée à g */
	free(t2);

	/* t1 va être free ici : */
	free_grille(g);
}

int main()
{
	CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Tests Rendu A", 0, 0);

    CU_add_test(suite, "Tests Grille", tests_Grille);
	CU_add_test(suite, "Tests Tuile", tests_Tuile);

	CU_add_test(suite, "Tests chargement Grille", tests_charger_Grille);
	CU_add_test(suite, "Tests chargement Tuiles", tests_charger_Tuiles);
	
	CU_add_test(suite, "Tests recouvrement complete d'une tuile", tests_recouvrement_Tuiles);
	CU_add_test(suite, "Tests pose tuile hors grille", tests_is_in_grid);
	CU_add_test(suite, "Tests pose tuile sur un lac", tests_dont_fill_lake);
	CU_add_test(suite, "Tests pose non connecté", tests_is_connected);
	CU_add_test(suite, "Tests ajout tuile safe", tests_ajout_tuile_safe);
	
	CU_add_test(suite, "Tests cases recouvertes", tests_cases_recouvertes);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

	return 0;
}
