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

#endif
