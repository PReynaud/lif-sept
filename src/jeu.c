#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "joueur.h"
#include "flotte.h"

void initialise_jeu(Jeu *un_jeu)
{
	un_jeu->tour_en_cours = 0;
	un_jeu->joueur_en_cours = 0;
	un_jeu->nb_joueur = 0;
	un_jeu->selection_flotte = NULL;
	un_jeu->selection_planete = NULL;
    un_jeu->tab_joueur =(Joueur *)malloc(sizeof(Joueur) * 10);
}

Jeu *creer_jeu()
{
	Jeu *un_jeu=(Jeu *)malloc(sizeof(Jeu));
    initialise_jeu(un_jeu);
    return un_jeu;
}


void liberer_jeu(Jeu *un_jeu)
{
    int i;
    for(i=0;i<un_jeu->nb_joueur;i++)
    {
        liberer_joueur(&un_jeu->tab_joueur[i]);
    }
    free(un_jeu->tab_joueur);
    un_jeu->tour_en_cours = 0;
    un_jeu->joueur_en_cours = 0;
    un_jeu->nb_joueur = 0;
    un_jeu->selection_flotte = NULL;
}

void detruire_jeu(Jeu **un_jeu)
{
    liberer_jeu(*un_jeu);
    free(*un_jeu);
    *un_jeu = NULL;
}

void ajouter_joueur(Jeu *un_jeu, Joueur *un_joueur)
{
	int i;
	i = un_jeu->nb_joueur;
	if(un_jeu->nb_joueur < 10)
	{
		un_jeu->tab_joueur[i] = *un_joueur;
		un_jeu->nb_joueur ++;
		set_numero_joueur(un_jeu->tab_joueur+i,i);
	}
	free(un_joueur);
}

void joueur_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	if(un_jeu->joueur_en_cours +1 < un_jeu->nb_joueur)
	{
		un_jeu->joueur_en_cours ++;
	}
	else
	{
		tour_suivant(un_jeu, un_terrain_espace);
		un_jeu->joueur_en_cours = 0;
	}
}

void tour_suivant(Jeu *un_jeu, Terrain_espace *un_terrain_espace)
{
	int metal = 0;
	int argent = 0;
	int carburant = 0;
	int population = 0;
	Case_terrain_espace *une_case_terrain_espace;
	int i;

	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		metal = 0;
		argent = 0;
		carburant = 0;
		population = 0;

		recuperer_ressource_planete(&un_jeu->tab_joueur[i], &metal, &argent, &carburant, &population);

		un_jeu->tab_joueur[i].metal += metal;
		un_jeu->tab_joueur[i].argent += argent;
		un_jeu->tab_joueur[i].carburant += carburant;
		un_jeu->tab_joueur[i].population += population;
		/*printf("Ressources du tour %d pour le joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", un_jeu->tour_en_cours, i, metal, argent, carburant, population);*/
		reinitialiser_mouvement_flotte(&(un_jeu->tab_joueur[i].tab_flotte[0]));

		un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant --;
		if(un_jeu->tab_joueur[i].tab_planete[0]->batiment_nb_tour_restant == 0) /*a completer pour gerer automatiquement chaque planete de chaque joueur*/
		{
		    validation_batiment(un_jeu->tab_joueur[i].tab_planete[0]);
		}

		un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant --; /*de meme*/
		if(un_jeu->tab_joueur[i].tab_planete[0]->unite_nb_tour_restant == 0)
		{
		    une_case_terrain_espace = get_case_terrain_espace(un_terrain_espace, un_jeu->tab_joueur[i].tab_planete[0]->x, un_jeu->tab_joueur[i].tab_planete[0]->y);
		    validation_creation_unite_planete(une_case_terrain_espace, &un_jeu->tab_joueur[i]);
		}
	}
	un_jeu->tour_en_cours++;
}

void afficher_info(Jeu *un_jeu)
{
	printf("Joueur en cours %d, tour en cours %d , nb de joueurs %d \n", un_jeu->joueur_en_cours, un_jeu->tour_en_cours,un_jeu->nb_joueur);
}

void validation_creation_unite_planete(Case_terrain_espace *une_case_terrain_espace, Joueur *un_joueur)
{
    Unite *une_unite;
    Flotte *une_flotte;
    Planete *une_planete = get_planete(une_case_terrain_espace);
    if(une_planete->unite_nb_tour_restant == 0)
    {
        if(une_planete->unite_en_cours == 1)
        {
            une_unite = creer_unite(PT_VIE_UNITE_1, PT_ATTAQUE_UNITE_1, PT_ACTION_UNITE_1, PT_DEPLACEMENT_UNITE_1, 10, PT_MOUVEMENT_UNITE_1);
            une_flotte = creer_flotte();
            ajouter_unite_flotte(une_flotte, une_unite);
            ajouter_flotte_joueur(un_joueur, une_flotte);
            ajouter_flotte(une_case_terrain_espace, &un_joueur->tab_flotte[un_joueur->nb_flotte - 1]);
        }
    }
}
void afficher_ressource_joueur(Jeu *un_jeu)
{
	int i;
	for(i=0;i<un_jeu->nb_joueur;i++)
	{
		printf("Ressources du joueur %d: \nMetal: %d \nArgent: %d \nCarburant: %d \nPopulation: %d\n\n", i, un_jeu->tab_joueur[i].metal, un_jeu->tab_joueur[i].argent, un_jeu->tab_joueur[i].carburant, un_jeu->tab_joueur[i].population);
	}
}
Joueur * get_ieme_joueur_jeu(Jeu * un_jeu,int i)
{
	return un_jeu->tab_joueur + i;
}

void placer_unite_flotte_en_haut(Terrain_combat * un_terrain_combat, Flotte * flotte)
{
	int i,m,n;
	Unite * une_unite;
	for(i=0;i<(flotte->taille_flotte);i++)
	{
		une_unite=get_unite_i_flotte(flotte,i);
		m=get_x_unite(une_unite);
		n=get_y_unite(une_unite);
		while(case_libre(un_terrain_combat, m,n))
		{
			set_y_unite(une_unite,n+1);
			m=get_x_unite(une_unite);
			n=get_y_unite(une_unite);
		}
			ajoute_unite_terrain(un_terrain_combat, une_unite,m,n);
	}
	
}

void placer_unite_flotte_en_bas(Terrain_combat * un_terrain_combat, Flotte * flotte)
{
	int i,m,n;
	Unite * une_unite;
	for(i=0;i<(flotte->taille_flotte);i++)
	{
		une_unite=get_unite_i_flotte(flotte,i);
		m=(un_terrain_combat->taille_combat_x)-1;
		n=(un_terrain_combat->taille_combat_y)-1;
		set_x_unite(une_unite,m);
		set_y_unite(une_unite,n);
		while(case_libre(un_terrain_combat, m,n))
		{
			set_y_unite(une_unite,n-1);
			m=get_x_unite(une_unite);
			n=get_y_unite(une_unite);
		}
			ajoute_unite_terrain(un_terrain_combat, une_unite,m,n);
	}
	
}



