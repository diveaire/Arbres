#if !defined(__ARBRE__)
#define __ARBRE__

/* Fichier permettant de donner la structure d'un arbre */
typedef struct Noeud
{
    int valeur;
    struct Noeud * gauche;
    struct Noeud * droite;
}Noeud;

typedef struct Arbre
{
    struct Noeud * racine;
} Arbre;

Noeud * creerNoeud(int valeur);

int arbreVide(Arbre * monArbre );
int estFeuille(Noeud * monNoeud);

int hauteurNoeud(Noeud *monNoeud);
int hauteurArbre(Arbre *monArbre);

void supprimerNoeud(Noeud * monNoeud);
void supprimerArbre(Arbre * monArbre);

#endif
