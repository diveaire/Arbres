#include <stdio.h>
#include <stdlib.h>

#include "header/arbre.h"


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- CREATION -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Fonction permettant de créer le Noeud d'un arbre */
Noeud * creerNoeud(int valeur){
    Noeud * nouveauNoeud = (Noeud *) malloc(sizeof(Noeud));
    if (nouveauNoeud == NULL ){
        perror("Erreur allocation nouveau noeud\n");
        exit(1);
    }
    nouveauNoeud->valeur=valeur;
    nouveauNoeud->gauche=NULL;
    nouveauNoeud->droite=NULL;
    return nouveauNoeud;
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- BOOLEEN -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Fonction permettant de retourner 1 si l'arbre est vide */
int arbreVide(Arbre * monArbre ){
    if (monArbre == NULL || monArbre->racine == NULL) return 1;
    return 0;
}

/* Fonction permettant de retourner 1 si le noeud est une feuille (pas de fils gauche/droite )*/
int estFeuille(Noeud * monNoeud){
    if (monNoeud->droite == NULL && monNoeud->gauche == NULL) return 1;
    return 0;
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- HAUTEUR --------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Fonction permettant de calculer la hauteur en fonction d'un noeud de départ */
int hauteurNoeud(Noeud *monNoeud){
    if (monNoeud == NULL) {
        return 0; // Un noeud nul a une hauteur de 0
    }

    // Calcul de la hauteur de chaque sous-arbre
    if( hauteurNoeud(monNoeud->gauche) >= hauteurNoeud(monNoeud->droite) ){
        return 1 + hauteurNoeud(monNoeud->gauche);
    }
    else{
        return 1 + hauteurNoeud(monNoeud->droite);
    }
}

/* Fonction permettant de calculer la hauteur d'un arbre */
int hauteurArbre(Arbre *monArbre){
    if (arbreVide(monArbre)) {
        return 0; // Cas de base: un arbre vide a une hauteur de 0
    }
    return hauteurNoeud(monArbre->racine); //calcul de la hauteur en fonction de la racine
}


// Permet de supprimer un noeud ainsi que ses fils 
void supprimerNoeud(Noeud * monNoeud){
    if (monNoeud == NULL) return;
    supprimerNoeud(monNoeud->gauche);
    supprimerNoeud(monNoeud->droite);
    free(monNoeud);

}
// Permet de supprimer un arbre
void supprimerArbre(Arbre * monArbre){
    if(monArbre == NULL || monArbre->racine == NULL ) return;
    supprimerNoeud(monArbre->racine);
    monArbre->racine = NULL;
}
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */