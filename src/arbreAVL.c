#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header/arbreAVL.h"


void ajoutDansArbre(Arbre * monArbre, int valeur){
    if (monArbre == NULL){
        printf("Erreur Arbre non Allouer\n");
        return;
    }
    if (arbreVide(monArbre)){
        monArbre->racine = creerNoeud(valeur);
    }else{
        monArbre->racine = ajoutValeur(monArbre->racine, valeur);
    }
    monArbre->racine = equilibreAVL(monArbre->racine);
}

// Fonctions d'insertion de l'AVL
Noeud * ajoutValeur(Noeud * monNoeud, int valeur){
    if (monNoeud == NULL){
        monNoeud = creerNoeud(valeur);
    }else if (monNoeud->valeur >= valeur ){
        // met à gauche 
        monNoeud->gauche = ajoutValeur(monNoeud->gauche, valeur);
    }else{
        // met à droite
        monNoeud->droite = ajoutValeur(monNoeud->droite, valeur);
    }
    return equilibreAVL(monNoeud);
}


/* Fonctions de calcul de hauteur d'un arbre */
int hauteur(Noeud * monNoeud){
    if(monNoeud==NULL){
        return -1;
    }
    else {
        if( hauteur(monNoeud->gauche) >= hauteur(monNoeud->droite) ){
            return 1 + hauteur(monNoeud->gauche);
        }
        else{
            return 1 + hauteur(monNoeud->droite);
        }
    }
}

/* Fonction de mesure du déséquilibre */
int desequilibre(Noeud * monNoeud){
    if(monNoeud==NULL){
        return 0;
    }else{
        // Si la différence des hauteurs est comprise entre 1 et -1, l'arbre est équilibré
        if( (hauteur(monNoeud->gauche)-hauteur(monNoeud->droite) <= 1) && (hauteur(monNoeud->gauche)-hauteur(monNoeud->droite) >= -1) ){ 
            return 0;
        }
        // Si la différence des hauteurs est inférieur à -1, le sous arbre droit a une hauteur nettement supérieur au sous arbre gauche
        else if(hauteur(monNoeud->gauche)-hauteur(monNoeud->droite)<-1) {
            return -1;
        }
        // Si la différence des hauteurs est supérieur à 1, le sous arbre gauche a une hauteur nettement supérieur au sous arbre droit
        else {
            return 1;
        }
    }
}


Noeud * rotationGauche(Noeud * monNoeud){
    Noeud * sd = monNoeud->droite;
    monNoeud->droite = sd->gauche;
    sd->gauche = monNoeud;
    monNoeud = sd;
    return monNoeud;
}

Noeud * rotationDroite(Noeud * monNoeud){
    Noeud * sg=monNoeud->gauche;
    monNoeud->gauche = sg->droite;
    sg->droite = monNoeud;
    monNoeud = sg;
    return monNoeud;
}

Noeud * rotationDroiteGauche(Noeud * monNoeud){
    Noeud * sd = monNoeud->droite;
    Noeud * sdg = sd->gauche;
    sd->gauche = sdg->droite;
    sdg->droite = sd;
    monNoeud->droite = sdg->gauche;
    sdg->gauche = monNoeud;
    monNoeud = sdg;
    return monNoeud;
}

Noeud * rotationGaucheDroite(Noeud * monNoeud){
    Noeud * sg=monNoeud->gauche;
    Noeud * sgd = sg->droite;
    sg->droite = sgd->gauche;
    sgd->gauche = sg;
    monNoeud->gauche = sgd->droite;
    sgd->droite = monNoeud;
    monNoeud = sgd;
    return monNoeud;
}


//Fonction de rangement d'un AVL
Noeud * equilibreAVL(Noeud* monNoeud){
    if(monNoeud != NULL){		
        int equilibre = desequilibre(monNoeud);
        if(equilibre == 0){
            // Si il n'y a pas de déséquilibre alors il s'agit d'un AVL
            //printf("AVL OK\n");
            return monNoeud;
        }else if(equilibre == -1){
            // Si le déséquilibre est négatif on effectue une rotation gauche
            Noeud * sd = monNoeud->droite;
            if(hauteur(sd->gauche)-hauteur(sd->droite)==1){
                //printf("rotationDroiteGauche\n");
                monNoeud = rotationDroiteGauche(monNoeud);
                return equilibreAVL(monNoeud);
            }else{
                //printf("rotationGauche\n");
                monNoeud = rotationGauche(monNoeud);
                return equilibreAVL(monNoeud);
            }
            
        }else if(equilibre == 1){
            // Si le déséquilibre est positif on effectue une rotation droite
            Noeud * sg=monNoeud->gauche;
            if(hauteur(sg->gauche)-hauteur(sg->droite)==-1){
                //printf("rotationGaucheDroite\n");
                monNoeud = rotationGaucheDroite(monNoeud);
                return equilibreAVL(monNoeud);
                
            }else{
                //printf("rotationDroite\n");
                monNoeud = rotationDroite(monNoeud);
                return equilibreAVL(monNoeud);
            }
            
        }
    }
    // Si l'arbre est null alors il est inutile de le trier, on le renvoit
    return monNoeud;
}

/* Fonction de recherche d'un mot dans un AVL */
Noeud * recherche(Noeud* monNoeud,int valeur){
    if(monNoeud==NULL){
        return NULL;
    }
    if(monNoeud->valeur == valeur){
        return monNoeud;
    }
    if(monNoeud->valeur > valeur){
        return recherche(monNoeud->gauche,valeur);
    }
    else{
        return recherche(monNoeud->droite,valeur);
    }
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
    for (int i=0;i<15;i++){
        ajoutDansArbre(&monArbre, i);
    }
    /*
    ajoutDansArbre(&monArbre, 1);
    afficher_arbre_ascii(&monArbre);
    ajoutDansArbre(&monArbre, 2);
    afficher_arbre_ascii(&monArbre);
    ajoutDansArbre(&monArbre, 3);
    afficher_arbre_ascii(&monArbre);
    ajoutDansArbre(&monArbre, 2);
    afficher_arbre_ascii(&monArbre);
    ajoutDansArbre(&monArbre, 9);
    afficher_arbre_ascii(&monArbre);
    ajoutDansArbre(&monArbre, 3);
    afficher_arbre_ascii(&monArbre);
    ajoutDansArbre(&monArbre, 6);
    afficher_arbre_ascii(&monArbre);
    ajoutDansArbre(&monArbre, 4);
    */

    /* AFFICHAGE */
    afficher_arbre_ascii(&monArbre);

    /* ARBRE VIDE ? */
    printf("Mon arbre %s vide\n", arbreVide(&monArbre)?"est":"n'est pas");


    /* HAUTEUR D'UN ARBRE */
    printf("la hauteur : %d\n", hauteurArbre(&monArbre));



    /* RECHERCHE */
    if (recherche(monArbre.racine, 4) != NULL){
        printf("4 Trouvé dans l'arbre\n");
    };

    /* SUPPRESSION */
    supprimerArbre(&monArbre);
    afficher_arbre_ascii(&monArbre);

    return 0;
}
