#include "include.h" // Main include file

int main(int argc, char* argv[]){

    // Menu
    int ChoixExercice = 0;

    // Exercice 1
    MyTime Depart, Arrive, Duree;

    // Exercice 2
    double *dTAB = NULL;
    double *A = NULL, *B = NULL;
    int C, D, i;

    // Exercice 3
    int max, indice, TailleTableau;
    int *TAB = NULL;

    while (ChoixExercice < 1 || ChoixExercice > 4){ // Saisie sécurisé
        system(CLEAR);
        printf("Bienvenue dans le TP2 :\nALGORITHMIQUE ET PROGRAMMATION-INF2033\n\nVeuillez entrer le numero de l'exercice (1 - 4): ");
        scanf("%d", &ChoixExercice); clear();
    }
    printf("\n");

    switch (ChoixExercice)
    {
    case 1:
        system(CLEAR);
        Depart.Hours = secureInt("Heure de depart (0+): ", 0);
        Depart.Minutes = secureInt("Minutes de depart (0+): ", 0);
        Depart.Seconds = secureInt("Secondes de depart (0+): ", 0);

        Arrive.Hours = secureInt("Heure d'Arrive (0+): ", 0);
        Arrive.Minutes = secureInt("Minutes d'Arrive (0+): ", 0);
        Arrive.Seconds = secureInt("Secondes d'Arrive (0+): ", 0);

        Duree = HORAIRE(Depart, Arrive);
        printf("Durée : %dh%dm%ds\n", Duree.Hours, Duree.Minutes, Duree.Seconds);
        break;
    case 2:
        system(CLEAR);
        TailleTableau = -1;
        while (TailleTableau <= 0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la taille du tableau a tester (1+): ");
            scanf("%d", &TailleTableau); clear();
        }
        dTAB = (double*)malloc(sizeof(double)*TailleTableau);
        for (i = 0; i < TailleTableau; i++){
            system(CLEAR);
            printf("Veuillez entrer la valeur N°%d/%d (Negative ou Positive): ", i + 1, TailleTableau);
            while (scanf("%lf", &dTAB[i]) != 1){ // Saisie sécurisé      
                clear();
            }
        }
        Split(TailleTableau, dTAB, &A, &B, &C, &D);

        printf("Elements positifs TP : "); afficheDouble(A, C);
        printf("Elements negatifs TN : "); afficheDouble(B, D);

        free(A);
        free(B);
        free(dTAB);
        break;
    case 3:
        system(CLEAR);
        TailleTableau = -1;
        while (TailleTableau <= 0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la taille du tableau a tester (1+): ");
            scanf("%d", &TailleTableau); clear();
        }
        TAB = (int*)calloc(TailleTableau, sizeof(int));
        srand(time(NULL));
        chargement_aleatoire(TAB, TailleTableau);
        affiche(TAB, TailleTableau);
        printf("\n");
        tabmax_place(TAB, TailleTableau, &max, &indice);
        printf("Max : %d\nIndice : %d\n", max, indice);
        break;
    case 4:
        system(CLEAR);
        TailleTableau = -1;
        while (TailleTableau <= 0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la taille du tableau a tester (1+): ");
            scanf("%d", &TailleTableau); clear();
        }
        TAB = (int*)calloc(TailleTableau, sizeof(int));
        for (i = 0; i < TailleTableau; i++){
            system(CLEAR);
            printf("Veuillez entrer la valeur N°%d/%d: ", i + 1, TailleTableau);
            while (scanf("%d", &TAB[i]) != 1){ // Saisie sécurisé      
                clear();
            }
        }
        printf("Soit le tableau non trie : "); affiche(TAB, TailleTableau);
        bulle(TAB, TailleTableau);
        printf("Le tableau trie correspondant : "); affiche(TAB, TailleTableau);
        sleep(3);
        indice = -1;
        while (indice <= 0){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer la valeur a inserer : ");
            scanf("%d", &indice); clear();
        }
        insertion(&TAB, &TailleTableau, indice);
        affiche(TAB, TailleTableau);
        break;
    }
    return 0;
}