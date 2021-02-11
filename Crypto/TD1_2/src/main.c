#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cesar.h"

int main (int argc, char* argv[]){
    int key;
    int i;

    if (argc >= 5){
        key = atoi(argv[1]);
        
        if (strcmp(argv[2], "-chiff") == 0){
            CHIFF_CESAR(key, argv[3], argv[4]);
        } else if (strcmp(argv[2], "-dechiff") == 0){
            DECHIFF_CESAR(key, argv[3], argv[4]);
        } else if (strcmp(argv[2], "-chiffASCII") == 0){
            CESAR(key, argv[3], argv[4], 3);
        } else if (strcmp(argv[2], "-dechiffASCII") == 0){
            CESAR(key, argv[3], argv[4], 2);
        }
    }else{
        printf("Utilisation : prog <KEY> <MODE> <FILE IN> <FILE OUT>\n");
    }

    return 0;
}