#if !defined(__AFFICHAGE__)
#define __AFFICHAGE__

#include "arbre.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MAX_HAUTEUR 100
#define INFINI (1 << 20)

/* Structure permettant de faire une représentation ascii d'un arbre dans le terminal */
typedef struct NoeudASCII {
    struct NoeudASCII *gauche, *droite;
    int longueur_arete;
    int hauteur;
    int longueur_etiquette;
    int direction_parent;   // -1=gauche, 0=racine, 1=droite
    char etiquette[12];     // chaine pour contenir l'entier de l'arbre
} NoeudASCII;

/* Fonction Principale pour afficher un Arbre dans un terminal */
void afficher_arbre_ascii(Arbre *arbre);

/* Autre fonctions permettant de réaliser l'affichage */
void calculer_profil_gauche(NoeudASCII *noeud, int x, int y);
void calculer_profil_droit(NoeudASCII *noeud, int x, int y);
void calculer_longueurs_aretes(NoeudASCII *noeud);
void afficher_niveau(NoeudASCII *noeud, int x, int niveau);
NoeudASCII * construire_arbre_ascii(Noeud * monNoeud);
NoeudASCII *construire_noeud_ascii(Noeud *noeud);
void liberer_arbre_ascii(NoeudASCII *noeud);

#endif