#ifndef _PLANETE_H_
#define _PLANETE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * \file      Module terrain
 * \author
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Planète et ses particularités
 *
 * \details
 */


struct sPlanete;
typedef void (*Creation_batiment)(struct sPlanete*);
typedef void (*Validation_creation_batiment)(struct sPlanete*);

 typedef struct sPlanete
 {
     int x;
     int y;
     char nom_planete[30];
     /*lien sur proprietaire*/

     int batiment[10];
     int batiment_en_cours; /*indice dans le tableau du batiment en cours de construction*/
     int batiment_nb_tour_restant; /*entier indiquant le nombre de tours restants, si 0 on peut construire un batiment*/

     Validation_creation_batiment tab_fonction_validation[10];
     Creation_batiment tab_fonction_creation[10];

     int taille_utilisee;
     int taille_planete;
	 int habitabilite;
     bool planete_principale; /*1 si oui, 0 sinon */
     bool planete_colonisee; /*1 si oui, 0 sinon */

     int metal;
     int argent;
     int carburant;
     int population;

 }Planete;

void initialise_planete(Planete *une_planete, char nom_planete[30]);
Planete *creer_planete(char nom_planete[30]);

void set_nom_planete(Planete *une_planete, char nom[30]);
char* get_nom_planete(Planete *une_planete);
void set_position_planete(Planete *une_planete, int x, int y);
int get_position_x_planete(Planete *une_planete);
int get_position_y_planete(Planete *une_planete);
void set_taille_utilisee(Planete *une_planete, int taille_utilisee);
int get_taille_utilisee(Planete *une_planete);
void set_taille_planete(Planete *une_planete, int taille_planete);
int get_taille_planete(Planete *une_planete);
void set_habitabilite(Planete *une_planete, int nb);
int get_habitabilite(Planete *une_planete);
void set_planete_principale(Planete *une_planete, bool booleen);
bool get_planete_principale(Planete *une_planete);
void set_planete_colonisee(Planete *une_planete, bool booleen);
bool get_planete_colonisee(Planete *une_planete);

void set_metal(Planete *une_planete, int nb);
int get_metal(Planete *une_planete);
void set_argent(Planete *une_planete, int nb);
int get_argent(Planete *une_planete);
void set_carburant(Planete *une_planete, int nb);
int get_carburant(Planete *une_planete);
void set_population(Planete *une_planete, int nb);
int get_population(Planete *une_planete);

void modification_production_planete(Planete *une_planete, int metal, int argent, int carburant, int population);

void libere_planete(Planete *planete);
void detruire_planete(Planete **planete);

void afficher_planete(Planete *une_planete);
void afficher_batiment(Planete *une_planete);

void creation_batiment(Planete *une_planete, int choix);
void validation_batiment(Planete *une_planete);

void test_module_planete();



#endif
