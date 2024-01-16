#if !defined(__ARBREBINAIRESIMPLE__)
#define __ARBREBINAIRESIMPLE__

#include "arbre.h"
#include "pile.h"

Noeud * creerNoeud(int valeur);

void ajoutDansArbre(int valeur, Arbre * monArbre);
void ajoutValeur(int valeur, Noeud * monNoeud);
void ajoutSousArbre( Arbre * monArbre, int valeur, Arbre * monArbre2 );

int arbreVide(Arbre * monArbre );
int estFeuille(Noeud * monNoeud);

int hauteurArbre(Arbre *monArbre);
int hauteurNoeud(Noeud *monNoeud);

void supprimerArbreValeur(Arbre *monArbre, int valeur);
void supprimerNoeudValeur(Arbre *monArbre, Noeud *monNoeud, Noeud *parent, int valeur);
void supprimerArbre(Arbre * monArbre);
void supprimerNoeud(Noeud * monNoeud);

void afficheArbre(Noeud * monNoeud);

Noeud * rechercheArbreDFS(Arbre *monArbre, int valeur);
Noeud *rechercheNoeudDFS(Noeud *monNoeud, int valeur);

#endif