#include "library.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void clear(){ // Vide stdin
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void wait(){ // Pause
    printf("\nAppuyez sur entrée pour continuer :\n");
    getchar();
}

void Afficher(char* filePath){
    FILE* libraryFile;
    book tempBook;

    system(CLEAR);

    if (!(libraryFile = fopen(filePath, "r"))) {
        printf("Unable to oppen : %s\n", filePath);
        return;
    }

    printf("Library Contents :\n\n");
    while (fscanf(libraryFile, "%d %s %d", &(tempBook.id), tempBook.title, &(tempBook.nbOfPages)) != EOF){
        printf("ID : %d\nTitle : %s\nNbOfPages : %d\n\n", tempBook.id, tempBook.title, tempBook.nbOfPages);
    }

    wait();

    fclose(libraryFile);
}

char Recherche(char* filePath, int id){
    FILE* libraryFile;
    book tempBook;
    int bookFound;

    if (!(libraryFile = fopen(filePath, "r"))) {
        printf("Unable to oppen : %s\n", filePath);
        return 0;
    }

    bookFound = 0;
    while (fscanf(libraryFile, "%d %s %d", &(tempBook.id), tempBook.title, &(tempBook.nbOfPages)) != EOF){
        if (tempBook.id == id){
            bookFound = 1;
            break;
        }
    }
    fclose(libraryFile);

    return bookFound;
}

void Ajouter(char* filePath){
    FILE* libraryFile;
    book tempBook;
    int userChoice, scan, i;

    userChoice = scan = -1;
    while (scan != 0){
        scan = -1;
        while ((scan != 1) || (userChoice < 0)){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer l'ID du livre a ajouter : ");
            scan = scanf("%d", &userChoice);
            clear();
        }
        printf((scan = Recherche(filePath, userChoice)) ? "\nID indisponible" : "\nID disponible !\n");
        wait();
    }
    tempBook.id = userChoice;

    system(CLEAR);
    printf("Veuillez entrer le titre du livre: ");
    fgets(tempBook.title, MAX_BOOK_NAME, stdin);
    i = 0;
    while (tempBook.title[i] != '\0'){
        if (tempBook.title[i] == ' '){
            tempBook.title[i] = '-';
        }
        i++;
    }
    tempBook.title[i - 1] = '\0';

    userChoice = scan = -1;
    while ((scan != 1) || (userChoice < 0)){ // Saisie sécurisé
        system(CLEAR);
        printf("Veuillez entrer le nombre de pages du livre: ");
        scan = scanf("%d", &userChoice);
        clear();
    }
    tempBook.nbOfPages = userChoice;

    if (!(libraryFile = fopen(filePath, "a"))) {
        printf("Unable to oppen : %s\n", filePath);
        return;
    }

    fprintf(libraryFile, "\n%d %s %d", tempBook.id, tempBook.title, tempBook.nbOfPages);

    fclose(libraryFile);
}

char* substr(char* Src, int Start, int End){
    char* string;

    string = (char*)malloc(sizeof(char)*(End - Start + 1));
    memcpy(string, &Src[Start], End - Start);
    string[End - Start] = '\0';

    return string;
}

void Supprimer(char* filePath){
    FILE* libraryFile;
    book tempBook;
    int userChoice, scan;
    long FirstHalf, Splice, SecondHalf;
    char* before;
    char* after;

    userChoice = scan = -1;
    while (scan != 1){ // Get the right id
        scan = -1;
        while ((scan != 1) || (userChoice < 0)){ // Saisie sécurisé
            system(CLEAR);
            printf("Veuillez entrer l'ID du livre a supprimer : ");
            scan = scanf("%d", &userChoice);
            clear();
        }
        printf((scan = Recherche(filePath, userChoice)) ? "" : "\nCe livre n'existe pas !\n");
        if (!scan) wait();
    }

    if (!(libraryFile = fopen(filePath, "r"))) { // open the file
        printf("Unable to oppen : %s\n", filePath);
        return;
    }

    // Search the right book
    FirstHalf = 0;
    while (fscanf(libraryFile, "%d %s %d", &(tempBook.id), tempBook.title, &(tempBook.nbOfPages)) != EOF){
        if (tempBook.id == userChoice){
            break;
        }
        FirstHalf = ftell(libraryFile);
    }
    Splice = ftell(libraryFile);
    
    fseek(libraryFile, 0, SEEK_END);
    SecondHalf = ftell(libraryFile) - Splice;
    rewind(libraryFile);

    // Get the text before the book
    before = (char*)malloc(sizeof(char)*(FirstHalf+1));
    fread(before, 1, FirstHalf, libraryFile);
    before[FirstHalf] = '\0';

    fseek(libraryFile, Splice - FirstHalf + 1, SEEK_CUR);

    // Get the text after the book
    after = (char*)malloc(sizeof(char*)*(SecondHalf+1));
    fread(after, 1, SecondHalf, libraryFile);
    after[SecondHalf] = '\0';

    fclose(libraryFile);

    if (!(libraryFile = fopen(filePath, "w"))) { // open the file
        printf("Unable to oppen : %s\n", filePath);
        return;
    }
    
    // Write to file
    fprintf(libraryFile, "%s", before);
    if ((before[0] != '\0') && (after[0] != '\0')) fprintf(libraryFile, "\n");
    fprintf(libraryFile, "%s", after);

    free(after);
    free(before);

    fclose(libraryFile);
}