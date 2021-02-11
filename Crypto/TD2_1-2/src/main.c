#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vigenere.h"

int main(int argc, char* argv[]){
    int KeySize;
    char* Key;

    if ((argc >= 4) && (strcmp(argv[1], "-extract") == 0)){
            RECHERCHE_CLE(argv[2], argv[3], "extracted.txt");
            EXTRACTION_CLE("extracted.txt");
    } else if (argc >= 5){
        KeySize = DETERM_LONG_TEXTE(argv[4]);
        Key = (char*)malloc(sizeof(char)*(KeySize + 1));
        CHARGER_CLE(KeySize, Key, argv[4]);

        if (strcmp(argv[1], "-chiff") == 0){
            CHIFF_VIGENERE(KeySize, Key, argv[2], argv[3]);
        } else if (strcmp(argv[1], "-dechiff") == 0){
            DECHIFF_VIGENERE(KeySize, Key, argv[2], argv[3]);
        }
    }else{
        printf("Utilisation : prog <MODE> <FILE IN> <FILE OUT> <KEY>\n");
    }

    if (Key)
        free(Key);

    return EXIT_SUCCESS;
}