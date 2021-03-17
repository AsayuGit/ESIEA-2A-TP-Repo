#ifndef _LIBRARY_H
#define _LIBRARY_H

#include "defines.h"

typedef struct book {
    int id;
    int nbOfPages;
    char title[MAX_BOOK_NAME];
}book;

void clear();
void wait();
void Afficher(char* filePath);
char Recherche(char* filePath, int id);
void Ajouter(char* filePath);
void Supprimer(char* filePath);

#endif