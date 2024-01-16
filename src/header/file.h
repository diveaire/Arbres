#if !defined(FILE)
#define FILE
#include "arbre.h"
//définition d'un élément d'un pile de noeud
typedef struct ElementFile
{
    struct Noeud * monNoeud;
    struct ElementFile * derriere;
} ElementFile;

// définition d'une pile de manière générale
typedef struct File{
    ElementFile * premier;
} File;


ElementFile* creerElementFile(Noeud * monNoeud);
void enfile(File * file, Noeud * monNoeud);
Noeud * defile(File * file);
int tailleFile(File* file);
int fileVide(File* file);
void videFile(File *file);
ElementFile * PremierElm(File* file);
void afficheFile(File* file);


#endif
