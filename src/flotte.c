#include <stdlib.h>
#include <stdio.h>

#include "flotte.h"
#include "unite.h"

void initialise_flotte(Flotte *flotte)
{
    flotte->taille_maximum_flotte = 10; //valeur temporaire qu'il faudra éventuellemnt modifié
    flotte->taille_flotte = 0;
    flotte->tab_unite = (Unite *)malloc(sizeof(Unite)*flotte->taille_maximum_flotte);
}

Flotte *creer_flotte()
{
    Flotte *flotte=(Flotte *)malloc(sizeof(Flotte));
    initialise_flotte(flotte);
    return flotte;
}

void set_taille_maximum_flotte(Flotte *flotte,const int max)
{
    flotte->taille_maximum_flotte = max;
}

void set_taille_flotte(Flotte *flotte,const int nb)
{
    flotte->taille_flotte = nb;
}

int get_taille_maximum_flotte(Flotte *flotte)
{
    return flotte->taille_maximum_flotte;
}

int get_taille_flotte(Flotte *flotte)
{
    return flotte->taille_flotte;
}

void libere_flotte(Flotte *flotte)
{
    free(flotte->tab_unite);
    flotte->tab_unite = NULL;
    flotte->taille_maximum_flotte = 10; //valeur temporaire qu'il faudra éventuellemnt modifié
    flotte->taille_flotte = 0;
}

void detruit_flotte(Flotte **flotte)
{
    libere_flotte(*flotte);
    free(*flotte);
    *flotte = NULL;
}

int ajouter_unite_flotte(Flotte *flotte, Unite *unite)
{
    if(flotte->taille_flotte < flotte->taille_maximum_flotte)
    {
        flotte->tab_unite[flotte->taille_flotte] = *unite;
        flotte->taille_flotte ++;
        return 1;
    }
    else
    {
        return 0;
    }
}

void retirer_unite_flotte(Flotte *flotte,const int indice_unite)
{
    int i;
    if(flotte->taille_flotte > 0)
    {
        for(i=indice_unite;i<flotte->taille_maximum_flotte - 1;i++)
        {
            flotte->tab_unite[i] = flotte->tab_unite[i+1];
        }
        flotte-> taille_flotte --;
        return 1;
    }
    else{return 0;}
}

void afficher_flotte(Flotte *flotte)
{
    int i;
    for(i=0;i<flotte->taille_flotte;i++)
    {
        printf("|| Unite %d: pv = %d, pa = %d\n", i+1 , flotte->tab_unite[i].pt_vie, flotte->tab_unite[i].pt_action);
    }

}

void test_module_flotte()
{
    Flotte *flotte;
    Unite *unite1;
    Unite *unite2;
    Unite *unite3;
    unite1 = creer_unite();
    unite2 = creer_unite();
    unite3 = creer_unite();

    printf("Verif de la création de flottes\n");
    flotte = creer_flotte();

    ajouter_unite_flotte(flotte, unite1);
    ajouter_unite_flotte(flotte, unite2);
    ajouter_unite_flotte(flotte, unite3);

    set_pt_vie(&(flotte->tab_unite[0]), 10);
    set_pt_vie(&(flotte->tab_unite[1]), 15);
    set_pt_vie(&(flotte->tab_unite[2]), 20);

    afficher_flotte(flotte);

    retirer_unite_flotte(flotte, 1);
    ajouter_unite_flotte(flotte, unite3);
    set_pt_vie(&(flotte->tab_unite[2]), 30);
    afficher_flotte(flotte);

    if((flotte->taille_maximum_flotte == 10) && (flotte->taille_flotte == 3))
    {
		printf ("OK \n");
	}
	else
	{
		printf ("Echec\n");
	}



}

