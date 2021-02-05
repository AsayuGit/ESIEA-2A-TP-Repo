#ifndef _FUNCTION
#define _FUNCTION

#include "include.h"

void clear();
int cleanString(char* String);

// 2)
void saisir(Eleve *T, int nb);

// 3)
void afficher(Eleve *T, int nbeleves);

// 4)
void ajouter(Eleve **T, int* nb);

// 5)
bool recherche(Eleve *T, int nb, int i, char nm[20], char pnm[20]);

// 6)
void supprime(Eleve **T, int* nb, double moy);

#endif