#include "functions.h"

// Exercice 1
void displayFile(FILE* filePointer){ // 1)
    char currentCharacter;

    if ((currentCharacter = fgetc(filePointer)) != EOF){
        printf("%c", currentCharacter);
        displayFile(filePointer);
    }
}


void displayFromBottom(FILE* filePointer){ // 2)
    char currentCharacter;

    if ((currentCharacter = fgetc(filePointer)) != EOF){
        displayFromBottom(filePointer);
        printf("%c", currentCharacter);
    }
}

void displayLineByLine(FILE* filePointer){ // 3)
    char* currentLine;
    size_t buffSize;

    currentLine = NULL;
    if (getline(&currentLine, &buffSize, filePointer) != -1){
        printf("%s", currentLine);
        if (currentLine){
            free(currentLine);
        }
        displayLineByLine(filePointer);
    }
}

void displayLineByLineFromBottom(FILE* filePointer){ // 4)
    char* currentLine;
    size_t buffSize;
    int lineSize;

    currentLine = NULL;
    if ((lineSize = getline(&currentLine, &buffSize, filePointer)) != -1){
        displayLineByLineFromBottom(filePointer);
        printf("%s%c", currentLine, (currentLine[lineSize - 1] != '\n') ? '\n' : '\0');
        if (currentLine){
            free(currentLine);
        }
    }
}