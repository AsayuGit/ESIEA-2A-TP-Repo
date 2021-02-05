#include "function.h"

void clear(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int cleanString(char* String){
    int i = 0;
    while (String[i] != '\0')
    {
        if (String[i] == '\n'){
            String[i] = '\0';
            return i - 1;
        }
        i++;
    }
    
}

int secureInt(char *Question, int Min){
    int retour = Min - 1;
    while (retour < Min){ // Saisie sécurisé
        system(CLEAR);
        printf("%s", Question);
        scanf("%d", &retour); clear();
    }
    return retour;
}

// Exercice 1
MyTime HORAIRE(MyTime Depart, MyTime Arrive){
    MyTime Duree = {0};

    // Hours
    if (Arrive.Hours < Depart.Hours)
        Duree.Hours = 24;
    Duree.Hours += Arrive.Hours - Depart.Hours;

    // Minutes
    if (Arrive.Minutes < Depart.Minutes){
        Duree.Minutes = 60; Duree.Hours--;
    }
    Duree.Minutes += Arrive.Minutes - Depart.Minutes;

    // Seconds
    if (Arrive.Seconds < Depart.Seconds){
        Duree.Seconds = 60; Duree.Minutes--;
    }
    Duree.Seconds += Arrive.Seconds - Depart.Seconds;

    return Duree;
}

// Exercice 2
void Split(int N, double T[], double *TP[], double *TN[], int *nbp, int *nbn){
    int i, j, k;
    *nbn = 0;

    for (i = 0; i < N; i++){
        if (T[i] < 0.0){
            (*nbn)++;
        }
    }

    *nbp = N - *nbn;

    *TP = (double*)malloc(sizeof(double)*(*nbp));
    *TN = (double*)malloc(sizeof(double)*(*nbn));

    // Assignation
    j = 0; k = 0;
    for (i = 0; i < N; i++){
        if (T[i] < 0.0){
            (*TN)[j] = T[i];
            j++;
        }else{
            (*TP)[k] = T[i];
            k++;
        }
    }
}

// Exercice 3
void chargement_aleatoire(int T[], int nb){
    int i;
    for (i = 0; i < nb; i++){
        T[i] = rand()%99 + 1;
    }
}

// Exercice 3
void tabmax_place(int T[], int n, int *max, int *place){
    int i;

    *max = T[0];
    *place = 0;
    for (i = 1; i < n; i++){
        if (T[i] > *max){
            *max = T[i];
            *place = i;
        }
    }
}

// Exercice 4
void bulle(int T[], int n){
    int i, j, TEMP, TriEffectue;
    TriEffectue = 1;
    for (i = n; i > 2; i--){
        for (j = 1; j < n; j++){
            if (T[j - 1] > T[j]){
                TEMP = T[j - 1];
                T[j - 1] = T[j];
                T[j] = TEMP;
                TriEffectue = 0;
            }
        }
        if(TriEffectue)
            break;
    }
}

// Exercice 4
int place(int T[], int n, int X){
    int i;
    for (i = 0; i < n; i++){
        if (T[i] > X){
            return i;
        }
    }
    return n;
}

// Exercice 4
void insertind(int *T[], int *n, int X, int ind){
    int i, *TempTab;
    TempTab = (int*)malloc(sizeof(int)*(++(*n)));
    
    for (i = 0; i < ind; i++){
        TempTab[i] = (*T)[i];
    }
    TempTab[i] = X;
    for (i++; i < *n; i++){
        TempTab[i] = (*T)[i - 1];
    }
    free(*T);
    *T = TempTab;
}

// Exercice 4
void insertion(int *T[], int *n, int X){
    int i, *TempTab;
    if (*n == 0){
        free(*T);
        *T = (int*)malloc(sizeof(int)*(++(*n)));
        *T[0] = X;
    }else{
        insertind(T, n, X, place(*T, *n, X));
    }
}

// Exercice 4
void affiche(int *tab, int nb){
    int i;
    for (i = 0; i < nb; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void afficheDouble(double *tab, int nb){
    int i;
    for (i = 0; i < nb; i++){
        printf("%lf ", tab[i]);
    }
    printf("\n");
}