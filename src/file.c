#include <stdio.h>
#include <stdlib.h>
#include "header/file.h"
#include "header/arbre.h"

// Fonction qui permet de créer un nouvel ElementFile de File en respectant les allocations mémoires
ElementFile* creerElementFile(Noeud * monNoeud){
    ElementFile* nouveau = (ElementFile*) malloc(sizeof(ElementFile));
    if (nouveau == NULL){
        printf("Erreur, impossible d'allouer la mémoire à un élément.\n");
        exit(1);
    }
    nouveau->monNoeud=monNoeud;
    nouveau->derriere=NULL;
    return nouveau;
}


// Fonction qui permet d'emFiler une valeur dans une File
void enfile(File *file, Noeud *monNoeud) {
    ElementFile *nouveau = creerElementFile(monNoeud);
    if (file->premier == NULL) { // Si la file est vide
        file->premier = nouveau;
        return;
    }
    // Parcours de la file pour trouver le dernier élément
    ElementFile *courant = file->premier;
    while (courant->derriere != NULL) {
        courant = courant->derriere;
    }
    courant->derriere = nouveau; // Ajout du nouvel élément à la fin de la file
}


// Fonction qui fait 1 deFilement d'une File
Noeud * defile(File * file){
    Noeud * monNoeud=NULL;
    if (file != NULL){
        ElementFile * courant = file->premier;
        file->premier=courant->derriere;
        monNoeud = courant->monNoeud;
        free(courant);
    }
    return monNoeud;
}

// Fonction qui retourne la taille de la File
int tailleFile(File* file){
    if (file->premier == NULL) return 0;
    // entier correspondant à la taille initialisé à 1 car File->premier != NULL
    int taille=1;
    // nouvelle File permettant de ne pas perdre les valeurs deFiler
    File * tempfile = (File*)malloc(sizeof(File));
    // recupération du premier de la File
    ElementFile * courant = file->premier;
    while(courant != NULL){
        taille++;
        enfile(tempfile, defile(file));
        courant = file->premier;
    }
    // on remet la File dans le bon sens
    courant = tempfile->premier;
    while(courant != NULL){
        taille++;
        enfile(file, defile(tempfile));
        courant = tempfile->premier;
    }
    // on déalloue la File temporaire qui nous à permis de garder les valeurs
    free(tempfile);
    return taille;
}

// Fonction qui retourne vrai si la File est vide
int fileVide(File* file){
    return (file->premier == NULL);
}

// Fonction permettant de retourner le premier ElementFile de la File
ElementFile * PremierElm(File* file){
    ElementFile * courant = file->premier;
    //printf("%d", courant->valeur);
    return courant;
}


/* Fonction permettant de vider une file */
void videFile(File *file) {
    while (file->premier != NULL) {
        ElementFile *temp = file->premier;
        file->premier = file->premier->derriere;
        free(temp); // Libère l'espace mémoire de l'élément retiré
    }
}



// fonction qui permet de faire l'affichage de la File dans son ordre de défillement
void afficheFile(File* file){
    // nouvelle File permettant de ne pas perdre les valeurs deFiler pour l'affichage
    File* tempFile = (File*)malloc(sizeof(File));
    // récupération du premier de la File
    ElementFile * courant = file->premier;
    while (courant != NULL){
        printf("%d\n", courant->monNoeud->valeur);
        enfile(tempFile,defile(file));
        courant = file->premier;
    }
    //on change le pointeur de file
    file = tempFile;
    // on déalloue la File temporaire qui nous à permis de garder les valeurs
    free(tempFile);
}

/*
int main(void){
    File* maFile = (File*)malloc(sizeof(File));
    for (int i=0;i<10;i++){
        enFile(maFile,i+1);
    }
    afficheFile(maFile);
}
*/
