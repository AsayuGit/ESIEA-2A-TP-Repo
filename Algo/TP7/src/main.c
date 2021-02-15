#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "dic.h"

// Exercice 2

int main (int argc, char* argv[]){

    FILE* fp;
    dictionary* dic;
    int userChoice;
    int scan;

    // Exercice 1
    // 5)
/*
    fp = fopen("text1.txt", "r+");

    displayFile(fp); // 1) 
    
    printf("\n\n"); 
    rewind(fp);
    
    displayFromBottom(fp); // 2)
    
    printf("\n\n");
    rewind(fp);
    
    displayLineByLine(fp); // 3)

    printf("\n\n");
    rewind(fp);

    displayLineByLineFromBottom(fp); // 4)

    fclose(fp);
*/
    // Exercice 2

    dic = loadDicFromFile("dic.txt"); // Load Dictionary into memory

    while (1){ // Main Loop
        userChoice = scan = -1;
        while ((scan != 1) || (userChoice < 0) || (userChoice > 4)){ // Saisie sécurisé
            system(CLEAR);
            printf("TP7\n\n"
            "0) Quitter\n"
            "1) Affichier Dic\n"
            "2) Ajouter un mot\n"
            "3) Rechercher un mot\n"
            "4) Supprimer un mot\n\n"
            "Veuillez selectionner une action: \n");
            scan = scanf("%d", &userChoice);
            clear();
        }
        switch (userChoice)
        {
        case 0:
            goto Exit;
            break;
        case 1:
            listDic(dic);
            break;
        
        case 2:
            AddWordToDictionary(&dic);
            break;
        
        case 3:
            SearchWordInDic(dic);
            break;

        case 4:
            DeleteWordInDic(&dic);
            break;
        default:
            break;
        }
    }

Exit:
    
    saveDicToFile(dic, "dic.txt");
    FreeDic(&dic);

    return 0;
}