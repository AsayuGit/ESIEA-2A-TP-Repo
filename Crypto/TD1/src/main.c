#include <stdio.h>
#include <string.h>

#include "crypto.h"

int main (int argc, char* argv[]){
    char cle[26];
    int i;
    
    if (argc >= 5){
        if (CHARGER_CLE(cle, argv[1])){
            for (i = 0; i < 26; i++){
                printf("%c", cle[i]);
            }
            printf("\n");
        }else{
            printf("Clée Introuvable !\n");
        }

        if (strcmp(argv[2], "-chiff") == 0){
            CHIFF_MONO_ALPHA(cle, argv[3], argv[4]);
        } else if (strcmp(argv[2], "-dechiff") == 0){
            DECHIFF_MONO_ALPHA(cle, argv[3], argv[4]);
        }
    }else{
        printf("Utilisation : prog <KEY PATH> <MODE> <FILE IN> <FILE OUT>\n");
    }

    return 0;
}