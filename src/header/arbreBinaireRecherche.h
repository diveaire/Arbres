#if !defined(__ARBREBINAIRERECHERCHE__)
#define __ARBREBINAIRERECHERCHE__

#include "arbre.h"
#include "affichageArbre.h"

void ajoutValeur(int valeur, Noeud * monNoeud);

int profondeurNoeud(Noeud * noeud, int valeur, int profondeur);
int profondeurArbre(Arbre * monArbre, int valeur);

Noeud * rechercheNoeud(Noeud *monNoeud, int valeur);
Noeud * rechercheArbre(Arbre *monArbre, int valeur);

#endif