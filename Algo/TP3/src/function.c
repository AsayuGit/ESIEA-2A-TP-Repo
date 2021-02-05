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

// 2)
void saisir(Eleve *T, int nb){
    int i;
    for (i = 0; i < nb; i++){
        system(CLEAR);
        printf("Veuillez entrer le NOM et Prénom de l'élève N°%d : ", i + 1);
        scanf("%s %s", T[i].Nom, T[i].Prenom); clear();
        cleanString(T[i].Nom);
        cleanString(T[i].Prenom);
        system(CLEAR);
        T[i].Moyenne = -1.0;
        while (T[i].Moyenne < 0.0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la moyenne de l'élève N°%d : ", i + 1);
            scanf("%lf", &T[i].Moyenne); clear();
        }
    }
}

// 3)
void afficher(Eleve *T, int nbeleves){
    int i;
    if (nbeleves <= 0){
        printf("Il ny a aucun élève dans la classe\n");
        return;
    }
    for (i = 0; i < nbeleves; i++){
        printf("L'Eleve N°%d s'apelle %s %s et a une moyenne de %lf \n", i + 1, T[i].Nom, T[i].Prenom, T[i].Moyenne);
    }
}

// 4)
void ajouter(Eleve **T, int* nb){
    int i;
    Eleve* NewArray;
    NewArray = (Eleve*)malloc(sizeof(Eleve)*((*nb) + 1));
    // CopyOver
    for (i = 0; i < *nb; i++){
        NewArray[i] = (*T)[i];
    }
    free(*T);
    *T = NewArray;
    (*nb)++;
    // New Student details
    system(CLEAR);
    printf("Veuillez entrer le NOM et Prénom de l'élève N°%d : ", i + 1);
    scanf("%s %s", NewArray[i].Nom, NewArray[i].Prenom); clear();
    cleanString(NewArray[i].Nom);
    cleanString(NewArray[i].Prenom);
    system(CLEAR);
    NewArray[i].Moyenne = -1.0;
    while (NewArray[i].Moyenne < 0.0){ // Saisie sécurisé
        system(CLEAR);
        printf("Veuillez entrer la moyenne de l'élève N°%d : ", i + 1);
        scanf("%lf", &NewArray[i].Moyenne); clear();
    }
}

// 5)
bool recherche(Eleve *T, int nb, int i, char nm[20], char pnm[20]){
    if (i == nb){
        return false;
    }
    if ((strcmp(T[i].Nom, nm) == 0) && (strcmp(T[i].Prenom, pnm) == 0)){
        return true;
    }else{
        return recherche(T, nb, i + 1, nm, pnm);
    }
}

// 6)
void supprime(Eleve **T, int* nb, double moy){
    int i, j, nbD;
    Eleve* NewArray;

    nbD = 0;
    for (i = 0; i < *nb; i++){ // recherche du nombre d'élément a supprimer
        if ((*T)[i].Moyenne == moy){
            nbD++;
        }
    }
    if (nbD == 0){
        printf("Aucun élève n'a la moyenne recherché\n");
        sleep(2);
        return;
    }



    NewArray = (Eleve*)malloc(sizeof(Eleve)*(*nb - nbD));
    // CopyOver
    j = 0;
    for (i = 0; i < *nb; i++){
        if ((*T)[i].Moyenne != moy){
            NewArray[j] = (*T)[i];
            j++;
        }
    }
    free(*T);
    *nb -= nbD;
    *T = NewArray;
}