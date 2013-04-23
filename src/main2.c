#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "planete.h"
#include "case_terrain_espace.h"
#include "niveau.h"
#include "unite.h"
#include "terrain_espace.h"
#include "flotte.h"
#include "sauvegarde.h"
#include "terrain_combat.h"
#include "case_terrain_combat.h"
#include "joueur.h"
#include "jeu.h"
#include "affichage.h"

int main()
{
	
	Terrain_combat * un_match;
	  Flotte *flotte1;
    Unite *unite1;
    Unite *unite2;
    Unite *unite3;

	Flotte *flotte2;
    Unite *unite4;
    Unite *unite5;
    Unite *unite6;
	/*int i;
	char c;
	bool p;*/
	
	unite1 = creer_unite(10,5,2,2,2,5);
    unite2 = creer_unite(40,3,2,4,2,8);
    unite3 = creer_unite(10,5,2,2,1,5);

    printf("Verif de la création de flottes\n");
    flotte1 = creer_flotte();
afficher_flotte(flotte1);
    ajouter_unite_flotte(flotte1, unite1);
    ajouter_unite_flotte(flotte1, unite2);
    ajouter_unite_flotte(flotte1, unite3);
	afficher_flotte(flotte1);

    unite4 = creer_unite(30,5,2,2,2,5);
    unite5 = creer_unite(30,3,2,4,2,8);
    unite6 = creer_unite(30,5,2,2,1,5);
 printf("Verif de la création de flottes\n");
    flotte2 = creer_flotte();
afficher_flotte(flotte2);
    ajouter_unite_flotte(flotte2, unite4);
    ajouter_unite_flotte(flotte2, unite5);
    ajouter_unite_flotte(flotte2, unite6);
	afficher_flotte(flotte2);

	un_match=creer_terrain_combat(15,10);
	modification_terrain_combat(un_match,'E');
	affiche_terrain_combat(un_match);

	placer_unite_flotte_en_haut(un_match,flotte1);
	afficher_flotte(flotte1);
	affiche_terrain_combat(un_match);
	

	placer_unite_flotte_en_bas(un_match,flotte2);
	afficher_flotte(flotte2);
	affiche_terrain_combat(un_match);
	/*i=0;
	
	while(c!='q')
	{	
		printf("tour %d \n", i);
		un_tour_combat(un_match,flotte1);
		un_tour_combat(un_match,flotte2);
		reinitialiser_deplacement_unite_flotte(flotte1);
		reinitialiser_deplacement_unite_flotte(flotte2);printf("\n");
		reinitialiser_pt_action_unite_flotte(flotte1);
		reinitialiser_pt_action_unite_flotte(flotte2);
		afficher_flotte(flotte1);printf("\n");
		afficher_flotte(flotte2);
		printf("continuer?\n");
		do{
		scanf("%c",&c);
		}while((c!='q') &&(c!='o'));
		printf("ok!\n");
	}*/
	affichage_ecran_acceuil(un_match);
	affichage_ecran_combat(un_match);
	return 0;

}
