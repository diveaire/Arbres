#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header/arbreBinaireRecherche.h"




/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------ AJOUTS VALEURS ---------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Fonction recursive permettant d'ajouter une valeur sur une feuille par rapport à un noeud de départ en respectant les règles de l'arbre binaire de recherche */
void ajoutValeur(int valeur, Noeud * monNoeud){
    if (valeur <= monNoeud->valeur){
        // met à gauche 
        if (monNoeud->gauche == NULL ) {
            monNoeud->gauche = creerNoeud(valeur);
        }else{
            ajoutValeur(valeur, monNoeud->gauche);
        }
    }else{
        // met à droite
        if (monNoeud->droite == NULL ) {
            monNoeud->droite = creerNoeud(valeur);
        }else{
            ajoutValeur(valeur, monNoeud->droite);
        }
    }
}

/* Fonction permettant d'ajouter une valeur dans un arbre binaire de recherche */
void ajoutDansArbre(int valeur, Arbre * monArbre){
    if (arbreVide(monArbre)){
        monArbre->racine = creerNoeud(valeur);
    }else{
        ajoutValeur(valeur, monArbre->racine);
    }
}


/* Fonction permettant d'ajouter un noeud et ses fils dans un autre arbre */
void ajoutSousArbre( Arbre * cible, Noeud * source ) {
    if (arbreVide(cible)){
        printf("L'arbre cible est vide'\n");
        return;
    }else if(source == NULL){
        printf("La source n'existe pas'\n");
        return;
    }
    // La valeur de la racine est déjà dans l'arbre
    ajoutDansArbre(source->valeur, cible);
    if (source->gauche != NULL){
        ajoutSousArbre(cible,source->gauche);
    }
    if (source->droite != NULL){
        ajoutSousArbre(cible,source->droite);
    }
}

/* Fonction permettant d'ajouter un sous arbre dans un autre arbre */
void ajoutArbreSousArbre( Arbre * cible, Arbre * source ) {
    if (arbreVide(cible)){
        printf("L'arbre cible est vide'\n");
        return;
    }else if(arbreVide(source)){
        printf("L'arbre source est vide'\n");
        return;
    }
    ajoutSousArbre(cible,source->racine);
}
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- PROFONDEUR ------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Permet de calculer la plus petite profondeur entre un noeud et la valeur d'un fils de ce noeud
    - La profondeur est à initialiser à 0 au lancement
*/
int profondeurNoeud(Noeud * noeud, int valeur, int profondeur){
    if (noeud == NULL) return -1; // vérification que le noeud existe

    if (valeur == noeud->valeur ) return profondeur;
    
    // Recherche dans le sous-arbre gauche
    if (valeur <= noeud->valeur){
        int profGauche = profondeurNoeud(noeud->gauche, valeur, profondeur + 1);
        if (profGauche != -1) return profGauche; // Si trouvé dans le sous-arbre gauche
    }
    // Recherche dans le sous-arbre droit
    return profondeurNoeud(noeud->droite, valeur, profondeur + 1);
}

/* Permet de calculer la plus petite profondeur entre la racine de l'arbre et un noeud de l'arbre en fonction de sa valeur 
    - retourne la profondeur ou -1 si 
    - l'arbre est vide
    - la valeur n'est pas dans l'arbre
*/
int profondeurArbre(Arbre * monArbre, int valeur){
    if (arbreVide(monArbre)){
        printf("Erreur Arbre vide\n");
        return -1;
    }
    return profondeurNoeud(monArbre->racine, valeur, 0);
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- RECHERCHE -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

Noeud *rechercheNoeud(Noeud *monNoeud, int valeur){
    if (monNoeud == NULL) {
        return NULL;
    }
    if (monNoeud->valeur == valeur ) {
        return monNoeud;
    }else if(valeur < monNoeud->valeur){
        Noeud *trouveGauche = rechercheNoeud(monNoeud->gauche, valeur);
        if (trouveGauche != NULL) {
            return trouveGauche;
        }
    }else{
        Noeud *trouveDroite = rechercheNoeud(monNoeud->droite, valeur);
        if (trouveDroite != NULL) {
            return trouveDroite;
        }
    }
    return NULL;
}


Noeud * rechercheArbre(Arbre *monArbre, int valeur){
    if (arbreVide(monArbre)) {
        return NULL;
    }
    Noeud *NoeudRecherche = rechercheNoeud(monArbre->racine, valeur);
    if (NoeudRecherche != NULL) {
        printf("La valeur %d est dans %p\n", NoeudRecherche->valeur, NoeudRecherche);
    } else {
        printf("Valeur non trouvée\n");
    }
    return NoeudRecherche;
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------ SUPPRESSION ------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

// Fonction pour trouver le noeud avec la plus petite valeur
Noeud* minValeurNoeud(Noeud* n) {
    Noeud* current = n;

    // Trouver le nœud le plus à gauche
    while (current && current->gauche != NULL) {
        current = current->gauche;
    }

    return current;
}

void supprimerNoeudValeur(Noeud *monNoeud, Noeud *parent, int valeur) {
    if (monNoeud == NULL) {
        return;
    }

    if (valeur < monNoeud->valeur) {
        supprimerNoeudValeur(monNoeud->gauche, monNoeud, valeur);
    } else if (valeur > monNoeud->valeur) {
        supprimerNoeudValeur(monNoeud->droite, monNoeud, valeur);
    } else {
        // Cas où le nœud est une feuille
        if (monNoeud->gauche == NULL && monNoeud->droite == NULL) {
            if (parent->gauche == monNoeud) {
                parent->gauche = NULL;
            } else {
                parent->droite = NULL;
            }
            free(monNoeud);
        }
        // Cas où le nœud a un seul enfant
        else if (monNoeud->gauche == NULL || monNoeud->droite == NULL) {
            Noeud *enfant = (monNoeud->gauche != NULL) ? monNoeud->gauche : monNoeud->droite;

            if (parent->gauche == monNoeud) {
                parent->gauche = enfant;
            } else {
                parent->droite = enfant;
            }
            free(monNoeud);
        }
        // Cas où le nœud a deux enfants
        else {
            Noeud *successeur = minValeurNoeud(monNoeud->droite);
            int succValeur = successeur->valeur;
            supprimerNoeudValeur(monNoeud, parent, succValeur);
            monNoeud->valeur = succValeur;
        }
    }
}

void supprimerArbreValeur(Arbre *monArbre, int valeur) {
    if (monArbre == NULL || monArbre->racine == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }
    supprimerNoeudValeur(monArbre->racine, NULL, valeur);
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- MAIN ---------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */


int main(void){
    srand(time(NULL)); // initialise la seed du random

    /* création et ajout de valeurs dans l'arbre */
    Arbre monArbre;
    monArbre.racine = NULL;
    // On remplis l'arbre
    for (int i=1;i<21;i++){
        int nb = rand() % 100;
        ajoutDansArbre(nb,&monArbre);
    }
    /* AFFICHAGE */
    afficher_arbre_ascii(&monArbre);

    /* ARBRE VIDE ? */
    printf("Mon arbre %s vide\n", arbreVide(&monArbre)?"est":"n'est pas");


    /* HAUTEUR D'UN ARBRE */
    printf("la hauteur : %d\n", hauteurArbre(&monArbre));
    printf("la hauteur de 2 : %d\n", hauteurNoeud(rechercheNoeud(monArbre.racine, 2)));


    /* PROFONDEUR */
    printf("Profondeur de 4 : %d\n",profondeurArbre(&monArbre, 4));
    printf("Profondeur de 6 : %d\n",profondeurArbre(&monArbre, 6));
    printf("Profondeur de 7 : %d\n",profondeurArbre(&monArbre, 7));
    printf("Profondeur de 11 : %d\n",profondeurArbre(&monArbre, 11));

    /* RECHERCHE */
    rechercheArbre(&monArbre, 4);

    /* SUPPRESSION */
    supprimerArbreValeur(&monArbre, 3);
    afficher_arbre_ascii(&monArbre);

    /* AJOUTER SOUS ARBRE */
    Arbre monArbre2;
    monArbre2.racine = NULL;

    for (int i=100; i<111 ; i++){
        ajoutDansArbre(i, &monArbre2);
    }
    ajoutArbreSousArbre(&monArbre, &monArbre2);
    afficher_arbre_ascii(&monArbre);

    supprimerArbre(&monArbre);
    return 0;
}