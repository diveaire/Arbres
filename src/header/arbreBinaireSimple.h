#if !defined(__ARBREBINAIRESIMPLE__)
#define __ARBREBINAIRESIMPLE__

#include "arbre.h"
#include "affichageArbre.h"
#include "file.h"

void ajoutDansArbre(int valeur, Arbre * monArbre);
void ajoutValeur(int valeur, Noeud * monNoeud);
void ajoutSousArbre( Arbre * monArbre, int valeur, Arbre * monArbre2 );

void supprimerArbreValeur(Arbre *monArbre, int valeur);
void supprimerNoeudValeur(Arbre *monArbre, Noeud *monNoeud, Noeud *parent, int valeur);


void afficheArbre(Noeud * monNoeud);

Noeud * rechercheArbreDFS(Arbre *monArbre, int valeur);
Noeud *rechercheNoeudDFS(Noeud *monNoeud, int valeur);

#endif