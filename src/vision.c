#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "vision.h"


/************************************************************************/
/* Initialisation, cr�ation et destruction                              */
/************************************************************************/

void initialiser_vision_terrain(Vision_terrain *une_vision_terrain, Terrain_espace *un_terrain, int indice_joueur)
{
	int i, j;
	
	une_vision_terrain->indice_joueur = indice_joueur;
	une_vision_terrain->terrain_espace = un_terrain;
	une_vision_terrain->vision_case = (Vision_case *)malloc(sizeof(Vision_case) * (get_taille_espace_x(un_terrain)*get_taille_espace_y(un_terrain)));
	for(i=0;i<un_terrain->taille_espace_y;i++)
	{
		for(j=0;j<un_terrain->taille_espace_x;j++)
		{
			initialiser_vision_case(&une_vision_terrain->vision_case[i*(un_terrain->taille_espace_x)+j], indice_joueur);
		}
	}
}

Vision_terrain* creer_vision_terrain(Terrain_espace* un_terrain, int indice_joueur)
{
	Vision_terrain* une_vision = (Vision_terrain*)malloc(sizeof(Vision_terrain));
	initialiser_vision_terrain(une_vision, un_terrain, indice_joueur);
	return une_vision;
}

void initialiser_vision_case(Vision_case* une_vision_case, int indice_joueur)
{
	une_vision_case->indice_joueur = indice_joueur;
	une_vision_case->centre_vision = 0;
	une_vision_case->champ_vision = JAMAIS_VISITEE;
}

void liberer_vision_case(Vision_case* une_vision_case)
{
	une_vision_case->indice_joueur = -1;
	une_vision_case->centre_vision = 0;
	une_vision_case->champ_vision = JAMAIS_VISITEE;
}

void liberer_vision_terrain(Vision_terrain* une_vision_terrain)
{
	une_vision_terrain->indice_joueur = -1;
	une_vision_terrain->terrain_espace = NULL;
	free(une_vision_terrain->vision_case);
}

void detruire_vision_terrain(Vision_terrain** une_vision_terrain)
{
	liberer_vision_terrain(*une_vision_terrain);
	free(*une_vision_terrain);
	une_vision_terrain = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

Vision_case* get_vision_case(Vision_terrain* une_vision, int x, int y)
{
	return &(une_vision->vision_case[y*(une_vision->terrain_espace->taille_espace_x)+x]);
}


/************************************************************************/
/* Fonctions qui vont d�finir la vision du terrain                      */
/************************************************************************/

/*fonction qui va parcourir tout le terrain et d�finir pour un joueur donn� ses centres de vision*/
void parcourir_terrain(Vision_terrain* une_vision, int indice_joueur)
{
	int i, j;
	Case_terrain_espace* une_case;
	Terrain_espace* un_terrain = une_vision->terrain_espace;
	Vision_case* une_vision_case;

	for(i=0;i<un_terrain->taille_espace_y;i++)
	{
		for(j=0;j<un_terrain->taille_espace_x;j++)
		{
			une_case = get_case_terrain_espace(un_terrain, j ,i);
			une_vision_case = get_vision_case(une_vision, j, i);
			/*on met toutes les cases pr�c�demment visit�e a VISITEE*/
			if (une_vision_case->champ_vision == AFFICHEE)
			{
				une_vision_case->champ_vision = VISITEE;
			}
			if(une_vision_case->centre_vision > 0)
			{
				une_vision_case->centre_vision = 0;
			}
			/*on calcule ensuite les centres de vision*/
			if(une_case->presence_flotte)
			{
				if(une_case->flotte->indice_joueur == indice_joueur)
				{
					une_vision_case->centre_vision = une_case->flotte->vision;
					une_vision_case->champ_vision = AFFICHEE;
				}
			}
			if (une_case->type_case_terrain_espace == 'P')
			{
				if(une_case->planete->indice_joueur == indice_joueur)
				{
					une_vision_case->centre_vision = une_case->planete->vision;
					une_vision_case->champ_vision = AFFICHEE;
				}
			}
		}
	}
	definir_vision(une_vision);
}

/*fonction qui � partir des centres de vision va calculer la vision pour les cases autour*/
void definir_vision(Vision_terrain* une_vision)
{
	int i, j;
	int rayon, k, l;
	Terrain_espace* un_terrain = une_vision->terrain_espace;
	Vision_case* une_vision_case1;
	Vision_case* une_vision_case2;

	for(i=0;i<un_terrain->taille_espace_y;i++)
	{
		for(j=0;j<un_terrain->taille_espace_x;j++)
		{
			une_vision_case1 = get_vision_case(une_vision, j, i);
			if (une_vision_case1->centre_vision > 0)
			{
				rayon = une_vision_case1->centre_vision;
				for(l = (i-rayon);l <= (i+rayon);l++)
				{
					for(k = (j-rayon);k <= (j+rayon);k++)
					{
						if((k>=0) && (k<un_terrain->taille_espace_y) && (l>=0) && (l<un_terrain->taille_espace_x))
						{
							une_vision_case2 = get_vision_case(une_vision, k, l);
							une_vision_case2->champ_vision = AFFICHEE;
						}
					}
				}
			}
		}
	}
}