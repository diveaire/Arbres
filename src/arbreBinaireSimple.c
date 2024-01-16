#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header/arbreBinaireSimple.h"


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------ AJOUTS VALEURS ---------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Fonction recursive permettant de descendre dans un arbre jusqu'à une feuille. et dès qu'une feuille est atteint, ajout du noeud */
void ajoutValeur(int valeur, Noeud * monNoeud){
    int nb = rand()%2;
    if (nb == 0){
        //met à gauche 
        //printf("Ajout de %d à gauche\n", valeur);
        if (monNoeud->gauche == NULL ) {
            monNoeud->gauche = creerNoeud(valeur);
        }else{
            ajoutValeur(valeur, monNoeud->gauche);
        }
    }else{
        //met à droite
        //printf("Ajout de %d à droite\n", valeur);
        if (monNoeud->droite != NULL ) {
            ajoutValeur(valeur, monNoeud->droite);
        }else{
            monNoeud->droite = creerNoeud(valeur);
        }
    }
}

/* Fonction permettant d'ajouter de façon aléatoire une valeur dans un arbre à gauche ou à droite */
void ajoutDansArbre(int valeur, Arbre * monArbre){
    if (arbreVide(monArbre)){
        monArbre->racine = creerNoeud(valeur);
    }else{
        ajoutValeur(valeur, monArbre->racine);
    }
}

/* Fonction permettant d'ajouter de façon aléatoire un sous arbre dans une autre arbre à la position d'une certaine valeur */
void ajoutSousArbre( Arbre * monArbre, int valeur, Arbre * monArbre2 ) {
    Noeud * monNoeud1 = rechercheNoeudDFS(monArbre->racine,valeur);
    if (monNoeud1 == NULL) {
        printf("La valeur (%d) n'est pas dans l'Arbre\n", valeur);
        return;
    }else if (arbreVide(monArbre2)){
        printf("L'arbre à ajouté est vide'\n");
        return;
    }
    Noeud * monNoeud2 = monArbre2->racine;
    if (monNoeud1->gauche == NULL){
        monNoeud1->gauche = monNoeud2;
    }else if (monNoeud1->droite == NULL) {
        monNoeud1->droite = monNoeud2;
    }else {
        Noeud * nouveau = monNoeud2;
        while ( nouveau->gauche != NULL && nouveau->droite != NULL ){
            int nb = rand()%2;
            if (nb){
                nouveau = nouveau->gauche;
            } else {
                nouveau = nouveau->droite;
            }
        }
        int nb=rand()%2;
        if (nb){ //on met le sous arbre à gauche
            (nouveau->gauche == NULL)? (nouveau->gauche = monNoeud1->gauche):(nouveau->droite = monNoeud1->gauche);
            monNoeud1->gauche = monNoeud2;
        } else { // on met le sous arbre à droite
            (nouveau->gauche == NULL)? (nouveau->gauche = monNoeud1->droite):(nouveau->droite = monNoeud1->droite);
            monNoeud1->droite = monNoeud2;
        }
    }
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- PROFONDEUR ------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Permet de calculer la plus petite profondeur entre un noeud et la valeur d'un fils de ce noeud
    - La profondeur est à initialiser à 0 au lancement
*/
int profondeurNoeud(Noeud * noeud, int valeur, int profondeur){
    if (noeud == NULL) return -1; // vérification que le noeud existe

    if (noeud->valeur == valeur) return profondeur;
    
    // Recherche dans le sous-arbre gauche
    int profGauche = profondeurNoeud(noeud->gauche, valeur, profondeur + 1);
    if (profGauche != -1) return profGauche; // Si trouvé dans le sous-arbre gauche

    // Recherche dans le sous-arbre droit
    return profondeurNoeud(noeud->droite, valeur, profondeur + 1);
}

/* Permet de calculer la plus petite profondeur entre la racine de l'arbre et un noeud de l'arbre en fonction de sa valeur 
    retour : la profondeur OU -1 si :
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
/* ---------------------------------------------------------------------------- DFS ----------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

Noeud *rechercheNoeudDFS(Noeud *monNoeud, int valeur) {
    if (monNoeud == NULL) {
        return NULL;
    }
    if (monNoeud->valeur == valeur) {
        return monNoeud;
    }

    Noeud *trouveGauche = rechercheNoeudDFS(monNoeud->gauche, valeur);
    if (trouveGauche != NULL) {
        return trouveGauche;
    }

    Noeud *trouveDroite = rechercheNoeudDFS(monNoeud->droite, valeur);
    if (trouveDroite != NULL) {
        return trouveDroite;
    }

    return NULL;
}


Noeud * rechercheArbreDFS(Arbre *monArbre, int valeur) {
    if (arbreVide(monArbre)) {
        return NULL;
    }
    Noeud *NoeudRecherche = rechercheNoeudDFS(monArbre->racine, valeur);
    if (NoeudRecherche != NULL) {
        printf("La valeur %d est dans %p\n", NoeudRecherche->valeur, NoeudRecherche);
    } else {
        printf("Valeur non trouvée\n");
    }
    return NoeudRecherche;
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- BFS ----------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Permet de faire la recherche en profondeur en fonction de Noeud contenu dans la file */
void recherche(File *file, int valeur) {
    if (fileVide(file)) {
        return;
    }

    // Défiler le nœud actuel
    Noeud *NoeudCourant = defile(file);

    // Traitement du nœud actuel
    //printf("TRAITEMENT DE %d\n", NoeudCourant->valeur);
    if (NoeudCourant->valeur == valeur) {
        printf("La valeur %d est dans %p\n", NoeudCourant->valeur, NoeudCourant);
        return;
    }

    // Enfiler les enfants s'ils existent parcourt largeur de gauche à droite
    if (NoeudCourant->gauche != NULL) {
        enfile(file, NoeudCourant->gauche);
    }
    if (NoeudCourant->droite != NULL) {
        enfile(file, NoeudCourant->droite);
    }

    // on recommence jusqu'a ce que la file soit vide
    recherche(file, valeur);
}

void rechercheArbreBFSRecursif(Arbre *monArbre, int valeur) {
    if (arbreVide(monArbre)) {
        printf("L'arbre est vide.\n");
        return;
    }

    // Créer et initialiser la file
    File *file = initFile();
    enfile(file, monArbre->racine);

    // Démarrer la recherche
    recherche(file, valeur);

    // Nettoyage
    supprimerFile(file);
}

void rechercheArbreBFSIteratif(Arbre *monArbre, int valeur) {
    if (arbreVide(monArbre)) {
        printf("L'arbre est vide.\n");
        return;
    }

    // Création et initialisation de la file
    File *file = (File *)malloc(sizeof(File));
    file->premier = NULL;

    // Enfiler le nœud racine
    enfile(file, monArbre->racine);

    while (!fileVide(file)) {
        Noeud * NoeudCourant = defile(file);

        // Traitement du nœud actuel
        if (NoeudCourant->valeur == valeur) {
            printf("La valeur %d est dans %p\n", NoeudCourant->valeur, NoeudCourant);
            videFile(file);
            free(file);
            return;
        }

        // Enfiler les enfants s'ils existent
        if (NoeudCourant->gauche != NULL) {
            enfile(file, NoeudCourant->gauche);
        }
        if (NoeudCourant->droite != NULL) {
            enfile(file, NoeudCourant->droite);
        }
    }

    printf("Valeur %d non trouvée.\n", valeur);
    videFile(file);
    free(file);
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------ SUPPRESSION ------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void supprimerNoeudValeur(Arbre *monArbre, Noeud *monNoeud, Noeud *parent, int valeur) {
    if (monNoeud == NULL) {
        return;
    }

    if (monNoeud->valeur == valeur) {
        Noeud *remplacement = NULL;
        
        // Cas 1: Le noeud est une feuille
        if (estFeuille(monNoeud)) {
            remplacement = NULL;
        }
        // Cas 2: Le noeud a un seul enfant
        else if (monNoeud->gauche == NULL || monNoeud->droite == NULL) {
            remplacement = (monNoeud->gauche != NULL) ? monNoeud->gauche : monNoeud->droite;
        }
        // Cas 3: Le noeud a deux enfants
        else {
            remplacement = monNoeud;
            Noeud * ParentRemplacant = NULL;
            while (!estFeuille(remplacement)){
                ParentRemplacant = remplacement;
                remplacement = (remplacement->gauche != NULL) ? remplacement->gauche : remplacement->droite;
            }
            // Supprimer l'hérédité du parent sur le remplaçant (pour évité la boucle de pointeur)
            (ParentRemplacant->gauche == remplacement)? (ParentRemplacant->gauche = NULL) : (ParentRemplacant->droite = NULL);

            // Redirection des fils du noeud à supprimer sur la feuille qui va le remplacer
            remplacement->gauche = monNoeud->gauche;
            remplacement->droite = monNoeud->droite;
            
        }


        // Réaffectation du pointeur du parent sur le remplaçant
        if (parent == NULL) {
            monArbre->racine = remplacement;
        } else if (parent->gauche == monNoeud) {
            parent->gauche = remplacement;
        } else {
            parent->droite = remplacement;
        }

        // Suppression du noeud
        free(monNoeud);
        return;
    }
    // Si le noeud n'est pas celui rechercher on cherche récursivement dans les fils
    supprimerNoeudValeur(monArbre, monNoeud->gauche, monNoeud, valeur);
    supprimerNoeudValeur(monArbre, monNoeud->droite, monNoeud, valeur);
}

void supprimerArbreValeur(Arbre *monArbre, int valeur) {
    if (monArbre == NULL || monArbre->racine == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }
    supprimerNoeudValeur(monArbre, monArbre->racine, NULL, valeur);
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
        ajoutDansArbre(i,&monArbre);
    }
    /* AFFICHAGE */
    afficher_arbre_ascii(&monArbre);

    /* ARBRE VIDE ? */
    printf("Mon arbre %s vide\n", arbreVide(&monArbre)?"est":"n'est pas");


    /* HAUTEUR D'UN ARBRE */
    printf("la hauteur : %d\n", hauteurArbre(&monArbre));
    printf("la hauteur de 2 : %d\n", hauteurNoeud(rechercheNoeudDFS(monArbre.racine, 2)));


    /* PROFONDEUR */
    printf("Profondeur de 4 : %d\n",profondeurArbre(&monArbre, 4));
    printf("Profondeur de 6 : %d\n",profondeurArbre(&monArbre, 6));
    printf("Profondeur de 7 : %d\n",profondeurArbre(&monArbre, 7));
    printf("Profondeur de 11 : %d\n",profondeurArbre(&monArbre, 11));

    /* RECHERCHE */

    rechercheArbreDFS(&monArbre, 4);
    rechercheArbreBFSRecursif(&monArbre, 10);
    //rechercheArbreBFSIteratif(&monArbre, 10);


    /* SUPPRESSION */
    supprimerArbreValeur(&monArbre, 3);
    afficher_arbre_ascii(&monArbre);

    /* AJOUTER SOUS ARBRE */
    Arbre monArbre2;
    monArbre2.racine = NULL;

    for (int i=100; i<111 ; i++){
        ajoutDansArbre(i, &monArbre2);
    }
    ajoutSousArbre(&monArbre, 5, &monArbre2);
    afficher_arbre_ascii(&monArbre);

    supprimerArbre(&monArbre);
    return 0;
}