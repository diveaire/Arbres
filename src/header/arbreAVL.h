#if !defined(__ARBREAVL__)
#define __ARBREAVL__

#include "arbre.h"
#include "affichageArbre.h"

void ajoutDansArbre(Arbre * monArbre, int valeur);
Noeud * ajoutValeur(Noeud * monNoeud, int valeur);
int hauteur(Noeud * monNoeud);
int facteurEquilibrage(Noeud * monNoeud);
Noeud * rotationGauche(Noeud * monNoeud);
Noeud * rotationGaucheDroite(Noeud * monNoeud);
Noeud * rotationDroite(Noeud * monNoeud);
Noeud * rotationDroiteGauche(Noeud * monNoeud);
Noeud * equilibreAVL(Noeud* monNoeud);
Noeud * recherche(Noeud* monNoeud,int valeur);


#endif
