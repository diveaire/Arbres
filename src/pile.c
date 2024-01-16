#include <stdio.h>
#include <stdlib.h>
#include "header/arbre.h"
#include "header/pile.h"


// Fonction qui permet de créer un nouvel element de pile en respectant les allocations mémoires
ElementPile* creerElementPile(Noeud * monNoeud){
    ElementPile* nouveau = (ElementPile*) malloc(sizeof(ElementPile));
    if (nouveau == NULL){
        printf("Erreur, impossible d'allouer la mémoire à un élément.\n");
        exit(1);
    }
    nouveau->noeud= monNoeud;
    nouveau->precedent=NULL;
    return nouveau;
}


// Fonction qui permet d'empiler une valeur dans une pile
void empile(Pile * pile,Noeud * monNoeud){
    ElementPile* courant = pile->haut;
    ElementPile* nouveau = creerElementPile(monNoeud);
    
    nouveau->precedent=courant;
    pile->haut=nouveau;
}


// Fonction qui fait 1 depilement d'une pile
Noeud * depile(Pile * pile){
    Noeud * monNoeud;
    if (pile != NULL){
        ElementPile* courant = pile->haut;
        pile->haut=courant->precedent;
        monNoeud = courant->noeud;
        free(courant);
    }
    return monNoeud;
}

// Fonction qui retourne la taille de la pile
int taillePile(Pile* pile){
    if (pile->haut == NULL) return 0;
    // entier correspondant à la taille initialisé à 1 car pile->haut != NULL
    int taille=1;
    // nouvelle pile permettant de ne pas perdre les valeurs depiler
    Pile* tempPile = (Pile*)malloc(sizeof(Pile));
    // recupération du haut de la pile
    ElementPile* courant = pile->haut;
    while(courant != NULL){
        taille++;
        empile(tempPile, depile(pile));
        courant = pile->haut;
    }
    // on remet la pile dans le bon sens
    courant = tempPile->haut;
    while(courant != NULL){
        taille++;
        empile(pile, depile(tempPile));
        courant = tempPile->haut;
    }
    // on déalloue la pile temporaire qui nous à permis de garder les valeurs
    free(tempPile);
    return taille;
}

// Fonction qui retourne vrai si la pile est vide
int pileVide(Pile* pile){
    return (pile->haut == NULL);
}

// Fonction permettant de retourner le premier element de la pile
ElementPile * premierElmPile(Pile* pile){
    ElementPile * courant = pile->haut;
    //printf("%d", courant->valeur);
    return courant;
}


// fonction qui permet de faire l'affichage de la pile dans son ordre de défillement
void affichePile(Pile* pile){
    // nouvelle pile permettant de ne pas perdre les valeurs depiler pour l'affichage
    Pile* tempPile = (Pile*)malloc(sizeof(Pile));
    // récupération du haut de la pile
    ElementPile * courant = pile->haut;
    while (courant != NULL){
        printf("%d\n", courant->noeud->valeur);
        empile(tempPile,depile(pile));
        courant = pile->haut;
    }
    //on remet la pile dans le bon sens
    courant = tempPile->haut;
    while (courant != NULL){
        empile(pile,depile(tempPile));
        courant = tempPile->haut;
    }
    // on déalloue la pile temporaire qui nous à permis de garder les valeurs
    free(tempPile);
}


/*
int main(void){
    Pile* maPile = (Pile*)malloc(sizeof(Pile));
    for (int i=0;i<10;i++){
        empile(maPile,i+1);
    }
    affichePile(maPile);
    free(maPile);
}
*/