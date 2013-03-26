#include <stdlib.h>
#include <stdio.h>

#include "planete.h"


void initialise_planete(Planete *planete)
{
    planete->x = 0;
    planete->y = 0;
    planete->nom_planete = (char*)malloc(sizeof(char) * 30);
    planete->planete_colonisee = 0;
    planete->planete_principale = 0;
    planete->taille_planete = 0; /* a modifier*/
    planete->taille_utilisee = 0;
}

Planete *creer_planete()
{
    Planete *planete=(Planete *)malloc(sizeof(Planete));
    initialise_planete(planete);
    return planete;
}

void libere_planete(Planete *planete)
{
    planete->x = 0;
    planete->y = 0;
    free(planete->nom_planete);
    planete->planete_colonisee = 0;
    planete->planete_principale = 0;
    planete->taille_planete = 0;
    planete->taille_utilisee = 0;
}

void detruit_planete(Planete **planete)
{
    libere_planete(*planete);
    free(*planete);
    *planete = NULL;
}

void set_nom_planete(Planete *planete, char nom[30])
{
    int i;
    for(i=0;i<30;i++)
    {
        planete->nom_planete[i]=nom[i];
    }
}

void set_taille_utilisee(Planete *planete, int taille_utilisee)
{
    planete->taille_utilisee = taille_utilisee;
}

int get_taille_utilisee(Planete *planete)
{
    return planete->taille_utilisee;
}

void set_taille_planete(Planete *planete, int taille_planete)
{
    planete->taille_planete = taille_planete;
}

int get_taille_planete(Planete *planete)
{
    return planete->taille_planete;
}

void set_planete_principale(Planete *planete, int booleen)
{
    if ((booleen == 0) || (booleen == 1))
    {
        planete->planete_principale = booleen;
    }
}

int get_planete_principale(Planete *planete)
{
    return planete->planete_principale;
}

void set_planete_colonisee(Planete *planete, int booleen)
{
    if ((booleen == 0) || (booleen == 1))
    {
        planete->planete_colonisee = booleen;
    }
}

int get_planete_colonisee(Planete *planete)
{
    return planete->planete_colonisee;
}

void affiche_planete(Planete *une_planete)
{
    printf("Infos planete %s:\n", une_planete->nom_planete);
    printf("Coordonnes: x = %d, y = %d \n", une_planete->x, une_planete->y);
    printf("Taille: %d/%d \n", une_planete->taille_utilisee, une_planete->taille_planete);
    printf("Planete colonisee: %d, planete principale: %d \n", une_planete->planete_colonisee, une_planete->planete_principale);
    printf("\n");
}

void test_module_planete()
{
    Planete *terre;
    printf("Verif de la création de planètes\n");
    terre = creer_planete();
    if((terre->taille_planete == 0))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}
    detruit_planete(&terre);
}