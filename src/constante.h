#ifndef _CONSTANTE_H_
#define _CONSTANTE_H_

/*Cr�ation des unit�s*/
#define PT_VIE_UNITE_1 50
#define PT_ATTAQUE_UNITE_1 10
#define PT_ACTION_UNITE_1 10
#define PT_DEPLACEMENT_UNITE_1 10
#define PT_MOUVEMENT_UNITE_1 10
#define NB_TOUR_UNITE_1 1
#define NB_METAL_UNITE_1 100

/*Constantes pour l'�cran*/
#define TAILLE_FENETRE_X 1280
#define TAILLE_FENETRE_Y 768
#define NOMBRE_BITS_COULEUR 32
#define TAILLE_TERRAIN_ESPACE_X 1280
#define TAILLE_TERRAIN_ESPACE_Y 600

#define TAILLE_MINIMAP_X 200
#define TAILLE_MINIMAP_Y 140

#define DEPLACEMENT_AFFICHAGE 2

/*l'ecran du combat (ou/et du l'espace)*/
#define TAILLE_ECRAN_COMBAT_X 640
#define TAILLE_ECRAN_COMBAT_Y 400
#define X_CARTE 0
#define Y_CARTE 0
#define X_INTERFACE 0
#define Y_INTERFACE (TAILLE_FENETRE_Y - TAILLE_FENETRE_Y/3)
#define X_BOUTON_PASSER 10
#define Y_BOUTON_PASSER 10
#define X_BOUTON_ATTAQUER 240
#define Y_BOUTON_ATTAQUER 10
#define X_TEXTE 100
#define Y_TEXTE (Y_INTERFACE +200)
#define TAILLE_X_BOUTON_ATTAQUER 200
#define TAILLE_Y_BOUTON_ATTAQUER 50
#define NOIR SDL_MapRGB(ecran->format,0,0,0);
#endif

