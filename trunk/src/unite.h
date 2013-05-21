#ifndef _UNITE_H_
#define _UNITE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "niveau.h"

/**
 * \file      Module unité
 * \author    Les queues de cheval
 * \version   0.1
 * \date      19 mars 2013
 * \brief     Unité et ses particularités
 *
 * \details
 */

typedef enum
{
	Chasseur,
	Destroyer,
	Destructeur
}TYPE_VAISSEAU;

typedef struct
{
	TYPE_VAISSEAU type;
	int indice_joueur;
	int indice_dans_flotte;
	int x_unite;
	int y_unite;

	int portee;
	int pt_vie;
	int pt_vie_total;

	int pt_attaque;
	int pt_attaque_total;
	int pt_action;
	int pt_action_total;

	int pt_deplacement;/*dans le combat*/
	int pt_deplacement_total;
	int pt_mouvement_unite;/*dans l'espace*/
	Niveau niveau_unite;
	/*ressources nécessaires*/
	/*compétence spéciale*/
}Unite;

void initialise_unite(Unite *unite_jeu, TYPE_VAISSEAU type);
Unite *creer_unite(TYPE_VAISSEAU type);

void liberer_unite(Unite *unite_jeu);
void detruire_unite(Unite **unite_jeu);

TYPE_VAISSEAU get_type_vaisseau(Unite* une_unite);
void set_portee(Unite *unite_jeu, const int x);
int get_portee(const Unite *unite_jeu);

void set_pt_vie(Unite *unite_jeu, const int x);
int get_pt_vie(const Unite *unite_jeu);

void set_x_unite(Unite *unite_jeu, const int x);
int get_x_unite(const Unite *unite_jeu);

void set_y_unite(Unite *unite_jeu, const int y);
int get_y_unite(const Unite *unite_jeu);

void set_pt_attaque(Unite *unite_jeu, const int x);
int get_pt_attaque(const Unite *unite_jeu);

void set_pt_action(Unite *unite_jeu, const int x);
int get_pt_action(const Unite *unite_jeu);

void set_pt_deplacement(Unite *unite_jeu, const int x);
int get_pt_deplacement(const Unite *unite_jeu);

void set_pt_mouvement_unite(Unite *unite_jeu, const int x);
int get_pt_mouvement_unite(const Unite *unite_jeu);

void set_indice_joueur_unite(Unite *unite,const int i);
int get_indice_joueur_unite(const Unite *unite);

void set_indice_unite_dans_flotte(Unite *unite,const int i);
int get_indice_unite_dans_flotte(const Unite *unite);
bool unite_peut_se_deplacer(const Unite *une_unite, const int x, const int y);
int calcul_distance_unite(const int x_depart, const int y_depart, const int x_arrivee, const int y_arrivee);

void enlever_pt_mouvement_combat_unite(Unite *une_unite, const int distance);
void enlever_pt_action_unite(Unite *une_unite, const int point);
void reinitialiser_mouvement_combat_unite(Unite *une_unite);
void reinitialiser_pt_action(Unite *une_unite);

void sauvegarde_unite(const Unite *une_unite, FILE* f);
Unite* ouverture_unite(FILE *f);

void test_module_unite();

#endif

