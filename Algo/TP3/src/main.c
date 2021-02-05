#include "include.h"


int main (int argc, char* argv[]){
    Eleve* Classe;
    int nombreEleves;
    char NOM[20];
    char Prenom[20];
    int choix;
    double moy;
    
    // 7)a)
    nombreEleves = 0;
    while (nombreEleves <= 0){ // Saisie sécurisé
        system(CLEAR);
        printf("Veuillez entrer le nombre d'élève a sasir : ");
        scanf("%d", &nombreEleves); clear();
    }
    Classe = (Eleve*)malloc(sizeof(Eleve)*nombreEleves);
    saisir(Classe, nombreEleves);
    
    // b)
    while (true) {
        choix = -1;
        while ((choix < 0) || (choix > 4)){ // Saisie sécurisé
            system(CLEAR);
            printf("Menu : \n\n" \
            "0) Quitter\n" \
            "1) Afficher\n" \
            "2) Ajouter\n" \
            "3) Rechercher\n" \
            "4) Supprimer\n\n" \
            "Veuillez choisir une option pour continuer :");
            scanf("%d", &choix); clear();
        }
        switch (choix)
        {
        case 0: // Quitter
            free(Classe);
            return 0;
            break;
        case 1: // Afficher
            afficher(Classe, nombreEleves);
            sleep(2);
            break;
        case 2: // Ajouter
            ajouter(&Classe, &nombreEleves);
            break;
        case 3: // Rechercher
            printf("Veuillez entrer le NOM et Prénom de l'élève a rechercher : ");
            scanf("%s %s", NOM, Prenom); clear();
            if (recherche(Classe, nombreEleves, 0, NOM, Prenom)){
                printf("L'élève %s %s existe dans la classe\n", NOM, Prenom);
            }else{
                printf("L'Eleve %s %s n\'existe pas dans la classe\n", NOM, Prenom);
            }
            sleep(2);
            break;
        case 4: // Supprimer
            moy = -1.0;
            while (moy < 0){ // Saisie sécurisé
                system(CLEAR);
                printf("Veuillez entrer la moyenne des élèves a supprimer : ");
                scanf("%lf", &moy); clear();
            }
            supprime(&Classe, &nombreEleves, moy);
            printf("Les eleves avec une moyenne de %lf ont ete supprime de la classe\n", moy);
            break;
        default:
            break;
        }
    }
}