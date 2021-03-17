#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "library.h"

int main (int argc, char* argv[]){
    int userChoice, scan;

    while (1){ // Main Loop
        userChoice = scan = -1;
        while ((scan != 1) || (userChoice < 0) || (userChoice > 4)){ // Saisie sécurisé
            system(CLEAR);
            printf("TP7\n\n"
            "0) Quitter\n"
            "1) Afficher les livres\n"
            "2) Ajouter un livre\n"
            "3) Rechercher un livre\n"
            "4) Supprimer un livre\n"
            "\nVeuillez selectionner une action: ");
            scan = scanf("%d", &userChoice);
            clear();
        }
        switch (userChoice)
        {
        case 0:
            goto Exit;
            break;
        case 1:
            Afficher("bdlivre.txt");
            break;
        case 2:
            Ajouter("bdlivre.txt");
            break;
        case 3:
            userChoice = scan = -1;
            while ((scan != 1) || (userChoice < 0)){ // Saisie sécurisé
                system(CLEAR);
                printf("Veuillez entrer l'ID du livre a rechercher : ");
                scan = scanf("%d", &userChoice);
                clear();
            }
            printf(Recherche("bdlivre.txt", userChoice) ? "\nCe livre est dans la bibliothèque\n" : "\nCe livre n'existe pas !\n");
            wait();
            break;
        case 4:
            Supprimer("bdlivre.txt");
            break;

        default:
            break;
        }
    }

Exit:
    return 0;
}