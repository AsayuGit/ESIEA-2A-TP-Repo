#ifndef _FUNCTION
#define _FUNCTION

#include "include.h"

void clear();
int cleanString(char* String);
int secureInt(char *Question, int Min);

// Exercice 1
MyTime HORAIRE(MyTime Depart, MyTime Arrive);

// Exercice 2
void Split(int N, double T[], double *TP[], double *TN[], int *nbp, int *nbn);

// Exercice 3
void chargement_aleatoire(int T[], int nb);

// Exercice 3
void tabmax_place(int T[], int n, int *max, int *place);

// Exercice 4
void bulle(int T[], int n);

// Exercice 4
int place(int T[], int n, int X);

// Exercice 4
void insertind(int *T[], int *n, int X, int ind);

// Exercice 4
void insertion(int *T[], int *n, int X);

// Exercice 4
void affiche(int *tab, int nb);

void afficheDouble(double *tab, int nb);


#endif