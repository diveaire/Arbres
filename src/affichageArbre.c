/*
    *** SOURCE : https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console ***
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header/affichageArbre.h"


int profil_gauche[MAX_HAUTEUR];
int profil_droit[MAX_HAUTEUR];
int ecart = 4;  // Ecart entre les noeuds gauche et droit
int afficheSuivant;


NoeudASCII *construire_noeud_ascii(Noeud *noeud) {
    NoeudASCII * noeudAscii;
    if (noeud == NULL) return NULL;

    noeudAscii = malloc(sizeof(NoeudASCII));
    noeudAscii->gauche = construire_noeud_ascii(noeud->gauche);
    noeudAscii->droite = construire_noeud_ascii(noeud->droite);

    if (noeudAscii->gauche != NULL){
        noeudAscii->gauche->direction_parent = -1;
    }
    if (noeudAscii->droite != NULL) {
        noeudAscii->droite->direction_parent = 1;
    }

    sprintf(noeudAscii->etiquette, "%d", noeud->valeur);
    noeudAscii->longueur_etiquette = strlen(noeudAscii->etiquette);

    return noeudAscii;
}

NoeudASCII * construire_arbre_ascii(Noeud * monNoeud) {
    NoeudASCII * noeudAscii;
    if (monNoeud == NULL) return NULL;
    noeudAscii = construire_noeud_ascii(monNoeud);
    noeudAscii->direction_parent = 0;
    return noeudAscii;
}


void liberer_arbre_ascii(NoeudASCII *noeud) {
    if (noeud == NULL) return;
    liberer_arbre_ascii(noeud->gauche);
    liberer_arbre_ascii(noeud->droite);
    free(noeud);
}

void calculer_profil_gauche(NoeudASCII *noeud, int x, int y) {
    int i, estGauche;
    if (noeud == NULL) return;

    estGauche = (noeud->direction_parent == -1);
    profil_gauche[y] = MIN(profil_gauche[y], x-((noeud->longueur_etiquette-estGauche)/2));
    if (noeud->gauche != NULL) {
        for (i=1; i <= noeud->longueur_arete && y+i < MAX_HAUTEUR; i++) {
            profil_gauche[y+i] = MIN(profil_gauche[y+i], x-i);
        }
    }

    calculer_profil_gauche(noeud->gauche, x-noeud->longueur_arete-1, y+noeud->longueur_arete+1);
    calculer_profil_gauche(noeud->droite, x+noeud->longueur_arete + 1, y + noeud->longueur_arete+1);
}

void calculer_profil_droit(NoeudASCII *noeud, int x, int y) {
    int i, nonGauche;
    if (noeud == NULL) return;

    nonGauche = (noeud->direction_parent != -1);
    profil_droit[y] = MAX(profil_droit[y], x+((noeud->longueur_etiquette-nonGauche)/2));
    if (noeud->droite != NULL) {
        for (i=1; i <= noeud->longueur_arete && y+i < MAX_HAUTEUR; i++) {
            profil_droit[y+i] = MAX(profil_droit[y+i], x+i);
        }
    }

    calculer_profil_droit(noeud->gauche, x-noeud->longueur_arete-1, y+noeud->longueur_arete+1);
    calculer_profil_droit(noeud->droite, x+noeud->longueur_arete+1, y+noeud->longueur_arete+1);
}

void calculer_longueurs_aretes(NoeudASCII *noeud) {
    int h, hmin, i, delta;
    if (noeud == NULL) return;

    calculer_longueurs_aretes(noeud->gauche);
    calculer_longueurs_aretes(noeud->droite);

    if (noeud->droite == NULL && noeud->gauche == NULL) {
        noeud->longueur_arete = 0;
    } else {
        if (noeud->gauche != NULL){
            for (i=0; i<noeud->gauche->hauteur && i < MAX_HAUTEUR ; i++){
                profil_droit[i] = -INFINI;
            }
            calculer_profil_droit(noeud->gauche, 0, 0);
            hmin = noeud->gauche->hauteur;
        } else {
            hmin = 0;
        }
        if (noeud->droite != NULL) {
            for (i=0; i<noeud->droite->hauteur && i < MAX_HAUTEUR; i++) {
                profil_gauche[i] = INFINI;
            }
            calculer_profil_gauche(noeud->droite, 0, 0);
            hmin = MIN(noeud->droite->hauteur, hmin);
        }else{
            hmin = 0;
        }
        delta = 4;
        for (i=0; i<hmin; i++) {
            delta = MAX(delta, ecart + 1 + profil_droit[i] - profil_gauche[i]);
        }
        
        //If the node has two children of height 1, then we allow the two leaves to be within 1, instead of 2 
        if (((noeud->gauche != NULL && noeud->gauche->hauteur == 1) || (noeud->droite != NULL && noeud->droite->hauteur == 1))&&delta>4) {
            delta--;
        }
            
        noeud->longueur_arete = ((delta+1)/2) - 1;
    }

    h = 1;
    if (noeud->gauche != NULL) {
        h = MAX(noeud->gauche->hauteur + noeud->longueur_arete + 1, h);
    }
    if (noeud->droite != NULL) {
        h = MAX(noeud->droite->hauteur + noeud->longueur_arete + 1, h);
    }
    noeud->hauteur = h;
}


void afficher_niveau(NoeudASCII *noeud, int x, int niveau) {
    int i, estGauche;
    if (noeud == NULL) return;
    
    estGauche = (noeud->direction_parent == -1);
    if (niveau == 0) {
        for (i=0; i<(x-afficheSuivant-((noeud->longueur_etiquette-estGauche)/2)); i++) {
            printf(" ");
        }
        afficheSuivant += i;
        printf("%s", noeud->etiquette);
        afficheSuivant += noeud->longueur_etiquette;
    } else if (noeud->longueur_arete >= niveau) {
        if (noeud->gauche != NULL) {
            for (i=0; i<(x-afficheSuivant-(niveau)); i++) {
                printf(" ");
            }
            afficheSuivant += i;
            printf("/");
            afficheSuivant++;
        }
        if (noeud->droite != NULL) {
            for (i=0; i<(x-afficheSuivant+(niveau)) ; i++) {
                printf(" ");
            }
            afficheSuivant += i;
            printf("\\");
            afficheSuivant++;
        }
    } else {
        afficher_niveau(noeud->gauche, x - noeud->longueur_arete - 1, niveau-noeud->longueur_arete - 1);
        afficher_niveau(noeud->droite, x + noeud->longueur_arete + 1, niveau - noeud->longueur_arete - 1);
    }
}


// Fonction principale pour l'affichage de l'arbre ASCII
void afficher_arbre_ascii(Arbre * arbre) {
    NoeudASCII *racine_ascii;
    int xmin, i;
    if (arbre == NULL || arbre->racine == NULL) return;

    racine_ascii = construire_arbre_ascii(arbre->racine);
    calculer_longueurs_aretes(racine_ascii);

    for (i=0; i<racine_ascii->hauteur && i < MAX_HAUTEUR; i++) {
        profil_gauche[i] = INFINI;
    }

    calculer_profil_gauche(racine_ascii, 0, 0);
    xmin = 0;
    for (i=0 ; (i<racine_ascii->hauteur && i<MAX_HAUTEUR) ; i++) {
        xmin = MIN(xmin, profil_gauche[i]);
    }

    for (i=0; (i<racine_ascii->hauteur) ; i++) {
        afficheSuivant = 0;
        afficher_niveau(racine_ascii, -xmin, i);
        printf("\n");
    }
    if (racine_ascii->hauteur >= MAX_HAUTEUR) {
        printf("( Cet arbre est plus haut que %d, et peut être dessiné incorrectement. )\n", MAX_HAUTEUR);
    }
    liberer_arbre_ascii(racine_ascii);
}
