#if !defined(__PILE__)
#define __PILE__
#include "arbre.h"
//définition d'un élément d'un pile de noeud
typedef struct ElementPile
{
    struct Noeud * noeud;
    struct ElementPile * precedent;
} ElementPile;

// définition d'une pile de manière générale
typedef struct Pile
{
    ElementPile * haut;
} Pile;

/* PROTOTYPES */
ElementPile * creerElementPile(Noeud * monNoeud);
int pileVide(Pile* pile);
void empile(Pile * pile, Noeud * monNoeud);
Noeud * depile(Pile * pile);
int taillePile(Pile* pile);
void affichePile(Pile* pile);
ElementPile * premierElmPile(Pile* pile);


#endif
